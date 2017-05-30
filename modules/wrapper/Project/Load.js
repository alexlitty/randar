module.exports = (randar) => {
    randar.Project.prototype.load = function(dir) {
        this.clear();
        this.directory(dir);
        this._onDisk = true;

        let project = JSON.parse(
            fs.readFileSync(this.directory().child('project.json').toString())
        );

        // Load basic item information.
        for (let itemId in project.items) {
            let item = project.items[itemId];

            this.binItems[itemId] = {
                id   : itemId,
                kind : item.kind,
                name : item.name,

                depended : [],
                depends  : []
            };
        }

        // Load basic folder information.
        for (let folderId in project.folders) {
            let folder = project.folders[folderId];

            this.binFolders[folderId] = {
                id   : folderId,
                name : folder.name
            };
        }

        // Expand item information.
        for (let itemId in project.items) {
            let item = project.items[itemId];

            this.binItems[itemId].depended = item.depended.map((otherItemId) => {
                if (!this.binItems[otherItemId]) {
                    throw new Error('Corrupted item dependencies');
                }
                return this.binItems[otherItemId];
            });

            this.binItems[itemId].depends = item.depends.map((otherItemId) => {
                if (!this.binItems[otherItemId]) {
                    throw new Error('Corrupted item dependencies');
                }
                return this.binItems[otherItemId];
            });
        }

        // Expand folder information.
        for (let folderId in project.folders) {
            let folder = project.folders[folderId];

            if (folder.parentFolder) {
                this.binFolders[folderId].parentFolder = this.binFolders[folder.parentFolder];
            }

            this.binFolders[folderId].folders = folder.folders.map((subfolderId) => {
                if (!this.binFolders[subfolderId]) {
                    throw new Error('Corrupted folder structure');
                }
                return this.binFolders[subfolderId];
            });

            this.binFolders[folderId].items = folder.items.map((itemId) => {
                if (!this.binItems[itemId]) {
                    throw new Error('Corrupted folder listing');
                }
                return this.binItems[itemId];
            });

            this.binFolders[folderId].items.forEach((item) => {
                item.folder = this.binFolders[folderId];
            });

            if (!this.binFolders[folderId].parentFolder) {
                this.bins[folderId] = this.binFolders[folderId];
            }
        }
    }
};
