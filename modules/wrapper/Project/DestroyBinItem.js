module.exports = (randar) => {
    /**
     * Destroys the bin item on disk.
     *
     * If the project has not been saved to disk yet, nothing happens.
     */
    randar.Project.prototype.destroyBinItem = function(item) {
        if (!this._onDisk) {
            return;
        }

        try {
            randar.removeDirectory(this.binItemDirectory());
        } catch (e) { }
    };
};
