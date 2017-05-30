module.exports = (randar) => {
    randar.Project.prototype.save = function() {
        let project = {
            name    : this.name,
            folders : {},
            items   : {}
        };

        for (let folderId in this.binFolders) {
            let folder = this.binFolders[folderId];

            project.folders[folderId] = {
                name         : folder.name,
                parentFolder : null,
                folders      : [],
                items        : []
            };

            if (folder.parentFolder) {
                project.folders[folderId].parentFolder = folder.parentFolder.id;
            }

            project.folders[folderId].folders = folder.folders.map((subfolder) => {
                return subfolder.id;
            });

            project.folders[folderId].items = folder.items.map((item) => {
                return item.id;
            });
        }

        for (let itemId in this.binItems) {
            let item = this.binItems[itemId];

            project.items[itemId] = {
                kind : item.kind,
                name : item.name,

                depended : item.depended,
                depends  : item.depends
            };

            this.saveBinItem(item);
        }

        fs.writeFileSync(
            this.directory().child('project.json').toString(),
            JSON.stringify(project)
        );

        this._onDisk = true;
    };
};
