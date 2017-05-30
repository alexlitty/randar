module.exports = (randar) => {
    randar.Project.prototype.load = function(dir) {
        this.clear();
        this.directory(dir);
        this._onDisk = true;

        let project = JSON.parse(
            fs.readFileSync(this.directory().child('project.json').toString())
        );

        for (let item of project.items) {
            this.binItems[item.id] = {
                id   : item.id,
                kind : item.kind,
                name : item.name,

                depended : [],
                depends  : []
            }
        }

        for (let item of project.items) {
            this.binItems[item.id].depended = item.depended.map((itemId) => {
                if (!this.binItems[itemId]) {
                    throw new Error('Corrupted item dependencies');
                }
                return this.binItems[itemId];
            });

            this.binItems[item.id].depends = item.depends.map((itemId) => {
                if (!this.binItems[itemId]) {
                    throw new Error('Corrupted item dependencies');
                }
                return this.binItems[itemId];
            });
        }

        for (let folder of project.folders) {
            this.binFolders[folder.id] = {
                id   : folder.id,
                name : folder.name
            };
        }

        for (let folder of project.folders) {
            if (folder.parentFolder) {
                this.binFolders[folder.id].parentFolder = this.binFolders[folder.parentFolder];
            }

            this.binFolders[folder.id].folders = folder.folders.map((folderId) => {
                if (!this.binFolders[folderId]) {
                    throw new Error('Corrupted folder structure');
                }
                return this.binFolders[folderId];
            });

            this.binFolders[folder.id].items = folder.items.map((itemId) => {
                if (!this.binItems[itemId]) {
                    throw new Error('Corrupted folder listing');
                }
                return this.binItems[itemId];
            });

            this.binFolders[folder.id].items.forEach((item) => {
                item.folder = this.binFolders[folder.id];
            });

            if (!this.binFolders[folder.id].parentFolder) {
                this.bins[folder.id] = this.binFolders[folder.id];
            }
        }

        for (let item of this.binItems) {
            this.loadBinItem(item);
        }
    }
};
