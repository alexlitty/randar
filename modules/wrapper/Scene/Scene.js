const _      = require('underscore');
const fs     = require('fs');
const mkdirp = require('mkdirp');
const path   = require('path');

function assertAction(action) {
    if (!_.isNumber(action.frame) || action.frame < 0) {
        throw new Error('Invalid frame index');
    }

    if (!_.isNumber(action.frameCount) || action.frameCount <= 0) {
        throw new Error('Invalid frame count');
    }

    if (action.kind === 'transform') {
        if (!_.isNumber(action.modelItemId) && !_.isNumber(action.geometryItemId)) {
            throw new Error('Invalid transform target');
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
        this.clear();
    }

    randar.scene = function() {
        return (new randar.Scene());
    }

    randar.Scene.prototype.kind = function() {
        return 'scene';
    }

    /**
     * Clears the scene.
     */
    randar.Scene.prototype.clear = function() {
        // Models in the scene.
        this.modelItems = {};

        // Geometries in the scene.
        this.geometryItems = {};

        // Actions in the scene. Frame states are built from these.
        this.actions = [];

        // Compiled frame states. Generated on-the-fly from actions as required.
        this.frameStates = [];

        // Current frame to draw by default.
        this.currentFrameIndex = 0;
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
                modelItems: {},
                geometryItems: {}
            };

            for (modelItemIndex in this.modelItems) {
                let modelItem = this.modelItems[modelItemIndex];
                previousFrame.modelItems[modelItem.id] = {
                    transform: {
                        position: { x: 0, y: 0, z: 0 }
                    }
                };
            }

            for (geometryItemIndex in this.geometryItems) {
                let geometryItem = this.geometryItems[geometryItemIndex];
                previousFrame.geometryItems[geometryItem.id] = {
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
                let transform;
                if (_.isNumber(action.modelItemId)) {
                    transform = frame.modelItems[action.modelItemId].transform;
                } else if (_.isNumber(action.geometryItemId)) {
                    transform = frame.geometryItems[action.geometryItemId].transform;
                }

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

    /**
     * Draws a frame.
     *
     * Assumes the frame state is up-to-date.
     *
     * The currentFrameIndex is used when no frameIndex is provided.
     */
    randar.Scene.prototype.drawFrame = function(canvas, frameIndex) {
        if (!_.isNumber(frameIndex)) {
            frameIndex = this.currentFrameIndex;
        }

        if (!_.isNumber(frameIndex) || frameIndex < 0) {
            throw new Error('Invalid frame index');
        }

        canvas.clear();

        let state = this.frameStates[frameIndex];
        if (!state) {
            return;
        }

        for (let geometryItemIndex in this.geometryItems) {
            let geometryItem = this.geometryItems[geometryItemIndex];

            let transform = randar.transform();
            transform.position(
                randar.toVector(state.geometryItems[geometryItem.id].transform.position)
            );

            canvas.draw(geometryItem.object(), transform);
        }

        for (let modelItemIndex in this.modelItems) {
            let modelItem = this.modelItems[modelItemIndex];

            let transform = randar.transform();
            transform.position(
                randar.toVector(state.modelItems[modelItem.id].transform.position)
            );

            canvas.draw(modelItem.object(), transform);
        }
    }

    /**
     * Saves the scene to disk.
     *
     * Frame states are not saved.
     */
    randar.Scene.prototype.save = function(directory) {
        directory = directory.toString();

        mkdirp.sync(directory);
        fs.writeFileSync(path.join(directory, 'scene.json'), JSON.stringify({
            geometryItems : _.map(_.keys(this.geometryItems), (key) => parseInt(key)),
            modelItems    : _.map(_.keys(this.modelItems), (key) => parseInt(key)),
            actions       : this.actions
        }));
    }

    /**
     * Loads the scene from disk.
     */
    randar.Scene.prototype.load = function(directory, project) {
        this.clear();
        directory = directory.toString();

        if (!project) {
            throw new Error('Project must be provided');
        }

        let data = JSON.parse(fs.readFileSync(path.join(directory, 'scene.json')));
        this.actions       = data.actions;

        this.geometryItems = {};
        for (let geometryItemId of data.geometryItems) {
            let item = project.items[geometryItemId];
            if (!item) {
                throw new Error('Scene uses unavailable item');
            }

            if (item.kind !== 'geometry') {
                throw new Error('Expected geometry project item');
            }

            this.geometryItems[geometryItemId] = item;
        }

        this.modelItems = {};
        for (let modelItemId of data.modelItems) {
            let item = project.items[modelItemId];
            if (!item) {
                throw new Error('Scene uses unavailable item');
            }

            if (item.kind !== 'model') {
                throw new Error('Expected model project item');
            }

            this.modelItems[modelItemId] = item;
        }
    }
}
