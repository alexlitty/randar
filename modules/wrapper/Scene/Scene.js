const _ = require('underscore');

function assertAction(action) {
    if (!_.isNumber(action.frame) || action.frame < 0) {
        throw new Error('Invalid frame index');
    }

    if (!_.isNumber(action.frameCount) || action.frameCount <= 0) {
        throw new Error('Invalid frame count');
    }

    if (action.kind === 'transform') {
        if (!_.isNumber(action.modelItemId)) {
            throw new Error('Invalid model item');
        }

        if (!action.translation) {
            throw new Error('Invalid translation');
        }

        for (let axis of ['x', 'y', 'z']) {
            if (!_.isNumber(action.translation[axis])) {
                throw new Error(`Invalid ${axis} translation`);
            }
        }
    }

    else {
        throw new Error('Invalid action kind');
    }
}

module.exports = (randar) => {
    randar.Scene = function() {
        // Models in the scene.
        this.modelItems = {};

        // Actions in the scene. Frame states are built from these.
        this.actions = [];

        // Compiled frame states. Generated on-the-fly from actions as required.
        this.frameStates = [];
    }

    randar.scene = function() {
        return (new randar.Scene());
    }

    /**
     * Calculates the number of frames in this scene.
     */
    randar.Scene.prototype.calculateFrameCount = function() {
        let finalFrame = 0;

        for (actionIndex in this.actions) {
            let action = this.actions[actionIndex];
            assertAction(action);

            let frameEnd = action.frame + action.frameCount - 1;
            if (frameEnd > finalFrame) {
                finalFrame = frameEnd;
            }
        }

        return finalFrame + 1;
    }

    /**
     * Compiles the state of a single frame.
     *
     * Requires the previous frame state to be compiled unless it is the first.
     */
    randar.Scene.prototype.compileFrame = function(frameIndex) {
        let previousFrame;

        // Get the previous frame.
        if (frameIndex > 0) {
            previousFrame = this.frameStates[frameIndex - 1];
        }

        // If this is the first frame, initialize it.
        else {
            previousFrame = {
                modelItems: {}
            };

            for (modelItemIndex in this.modelItems) {
                let modelItem = this.modelItems[modelItemIndex];
                previousFrame.modelItems[modelItem.id] = {
                    transform: {
                        position: { x: 0, y: 0, z: 0 }
                    }
                };
            }
        }

        // Deep copy the previous frame.
        let frame = JSON.parse(JSON.stringify(previousFrame));

        // Apply actions to the frame.
        for (actionIndex in this.actions) {
            let action = this.actions[actionIndex];
            assertAction(action);

            // Action does not apply to this frame.
            if (frameIndex < action.frame || frameIndex > (action.frame + action.frameCount - 1)) {
                continue;
            }

            // Apply transformation.
            if (action.kind === 'transform') {
                let transform = frame.modelItems[action.modelItemId].transform;
                for (let axis of ['x', 'y', 'z']) {
                    transform.position[axis] += action.translation[axis] / action.frameCount;
                }
            }
        }

        this.frameStates[frameIndex] = frame;
    }

    /**
     * Compiles all frame states.
     */
    randar.Scene.prototype.compile = function() {
        let finalFrameIndex = this.calculateFrameCount() - 1;

        for (let i = 0; i <= finalFrameIndex; i++) {
            this.compileFrame(i);
        }
    }
}
