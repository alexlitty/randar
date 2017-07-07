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
            this.window.camera().projection();
        }
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
     * Draws the item to the windowdow.
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

        else if (object.kind() === 'image') {
        }

        else {
            throw new Error('Observing item kind not implemented');
        }
    }
}
