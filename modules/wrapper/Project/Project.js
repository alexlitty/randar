module.exports = (randar) => {
    /**
     * A Randar Project, in all its glory.
     *
     * Every project, at its core, simply has items and folders. Folders are
     * used by the UI to organize items; They serve absolutely no functionality
     * otherwise.
     *
     * "Bins" are just folders without a parent. Bins exist in both the bins and
     * binFolders members.
     *
     * Items are wrappers for lower level resources.
     *
     * Project directories default to the current working directory.
     */
    randar.Project = function(dir) {
        this.clear();
        if (dir) {
            this.load(dir);
        }
    };

    /**
     * Sets or retrieves the project directory.
     */
    randar.Project.prototype.directory = function(newDirectory) {
        if (!arguments.length) {
            return this._directory;
        } else {
            this._directory = randar.path(newDirectory);
        }
    }

    /**
     * Require additional functionality.
     */
    require('./BinFolder.js')(randar);
    require('./BinItem.js')(randar);
    require('./Clear.js')(randar);
    require('./Save.js')(randar);
    require('./Load.js')(randar);

    /**
     * Creation helper function.
     */
    randar.project = function(dir) {
        return new randar.Project(dir);
    };
};
