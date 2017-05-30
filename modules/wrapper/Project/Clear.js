module.exports = (randar) => {
    randar.Project.prototype.clear = function() {
        this.bins       = {};
        this.binFolders = {};
        this.binItems   = {};

        this._directory = randar.path();
        this._onDisk    = false;
    };
};
