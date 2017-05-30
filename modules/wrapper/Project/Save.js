module.exports = (randar) => {
    randar.Project.prototype.save = function() {
        let project = {
            name    : this.name,
            folders : {},
            items   : {}
        };

        for (let folder of this.binFolders) {
            project.folders[folder.id] = {
                name         : folder.name,
                parentFolder : null,
                folders      : [],
                items        : []
            };

            if (folder.parentFolder) {
                project.folders[folder.id].parentFolder = folder.parentFolder.id;
            }

            for (let subfolder of folder.folders) {
                project.folders[folder.id].folders.push(subfolder.id);
            }

            for (let item of folder.items) {
                project.folders[folder.id].items.push(item.id);
            }
        }

        for (let item of project.binItems) {
            project.items[item.id] = {
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
