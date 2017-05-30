module.exports = (randar) => {
    randar.Project = function() {
        this.bins       = {};
        this.binFolders = {};
        this.binItems   = {};
    };

    randar.project = function() {
        return new randar.Project();
    };

    require('./BinFolder.js')(randar);
    require('./BinItem.js')(randar);
};
