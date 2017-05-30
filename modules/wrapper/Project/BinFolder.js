module.exports = (randar) => {
    /**
     * Adds a bin to the project.
     */
    randar.Project.prototype.addBin = function(name) {
        return this.addBinFolder(name, null);
    }

    /**
     * Adds a bin folder to the project.
     */
    randar.Project.prototype.addBinFolder = function(name, parentFolder) {
        if (!name) {
            if (parentFolder) {
                name = 'Untitled folder';
            } else {
                name = 'Untitled bin';
            }
        }

        let id = 0;
        while (this.binFolders[id]) {
            id++;
        }

        let folder = {
            id      : id,
            name    : name,
            folders : [],
            items   : []
        };

        this.moveBinFolder(folder, parentFolder);

        this.binFolders[folder.id] = folder;
        if (!parentFolder) {
            this.bins[folder.id] = folder;
        }

        return this.binFolders[folder.id];
    };

    /**
     * Removes a bin from the project.
     */
    randar.Project.prototype.removeBin = function(bin) {
        this.removeBinFolder(bin);
    }

    /**
     * Removes a bin folder from the project.
     */
    randar.Project.prototype.removeBinFolder = function(folder) {
        if (!this.binFolders[folder.id]) {
            throw new Error('Bin folder does not exist');
        }

        for (let subfolder of folder.folders) {
            this.removeBinFolder(subfolder);
        }

        for (let item of folder.items) {
            this.removeBinItem(item);
        }

        this.moveBinFolder(folder, null);

        delete this.binFolders[folder.id];
        delete this.bins[folder.id];
    };

    /**
     * Moves a bin folder.
     */
    randar.Project.prototype.moveBinFolder = function(folder, otherFolder) {
        if (folder.parentFolder) {
            let idx = folder.parentFolder.folders.indexOf(folder);
            if (idx > -1) {
                folder.parentFolder.folders.splice(idx, 1);
            }
            folder.parentFolder = null;
        }

        if (otherFolder) {
            otherFolder.folders.push(folder);
            folder.parentFolder = otherFolder;
        }
    };
};
