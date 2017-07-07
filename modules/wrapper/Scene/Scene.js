const _ = require('underscore');

module.exports = (randar) => {
    randar.Scene = function() {
        // Models in the scene.
        this.modelItems = {};

        // Actions in the scene. Frame states are built from these.
        this.actions = [];

        // Compiled frame states. Generated on-the-fly from actions as required.
        this.frameStates = [];
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
        for (actionId in this.actions) {
            let action = this.actions[actionId];

            // Validate the target frames.
            if (!_.isNumber(action.frame)) {
                throw new Error('Action has no frame defined:', action);
            }

            if (!_.isNumber(action.frameCount) || action.frameCount <= 0) {
                throw new Error('Action has invalid frame count:' action);
            }

            // Action does not apply to this frame.
            if (action.frame !== frameIndex) {
                continue;
            }

            // Apply transformation.
            if (action.kind === 'transform') {
                if (!action.modelItem) {
                    throw new Error('Transform action has no model item:', action);
                }

                if (!action.translation) {
                    throw new Error('Transform action has no translation:', action);
                }

                for (let axis in ['x', 'y', 'z']) {
                    if (!_.isNumber(action.translation[axis])) {
                        throw new Error(`Transform action has invalid ${axis} translation:`, action);
                    }

                    frame[action.modelItem][axis] += action.translation[axis];
                }
            }
        }

        this.frameStates[frameIndex] = frame;
    }

    /**
     * Compiles all frame states.
     */
    randar.Scene.prototype.compile = function() {
        let finalFrameIndex = 1000;

        for (let i = 0; i <= finalFrameIndex; i++) {
            this.compileFrame(i);
        }
    }
}
