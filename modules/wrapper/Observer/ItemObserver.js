module.exports = (randar) => {
    /**
     * A human-friendly project item observer.
     */
    randar.ItemObserver = function(ctx, item) {
        this.window = ctx.window(800, 600);
        this.window.fps(24);

        if (item) {
            this.item(item);
        }
    }

    /**
     * Gets or sets the item to observe.
     */
    randar.ItemObserver.prototype.item = function(item) {
        // Get the item.
        if (!item) {
            return this._item;
        }

        // Set the item.
        else {
            this._item = item;

            // Initialize the camera.
            this.camera().projection();
            this.camera().projection();
            this.camera().target(randar.vector(0, 0, 0));
            this.camera().position(randar.vector(0, 0, -5));
        }
    }

    /**
     * Gets the camera for the observer.
     */
    randar.ItemObserver.prototype.camera = function() {
        return this.window.camera();
    }

    /**
     * Runs a frame on the observer.
     */
    randar.ItemObserver.prototype.run = function() {
        this.window.clear();
        this.draw();
        this.window.present();
    }

    /**
     * Draws the item to the window.
     */
    randar.ItemObserver.prototype.draw = function() {
        let item = this.item();
        if (!item) {
            return;
        }

        let object = item.object();
        if (!object) {
            throw new Error('Item has no object');
        }

        if (!object.kind || !object.kind()) {
            throw new Error('Item object has no kind');
        }

        if (object.kind() === 'geometry') {
            this.window.draw(object);
        }

        else if (object.kind() === 'scene') {
            object.drawFrame(this.window);
        }

        else {
            throw new Error('Observing item kind not implemented');
        }
    }
}
