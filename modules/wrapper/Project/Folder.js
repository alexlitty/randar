module.exports = (randar) => {
    /**
     * A folder in a Randar project.
     *
     * Folders without parents are simply "bins."
     */
    randar.Project.Folder = function(project, name, parentFolder, id) {
        if (!(project instanceof randar.Project)) {
            throw new Error('Invalid project');
        }
        this.project = project;

        if (typeof name !== 'string') {
            throw new Error('Folder name must be provided as a string');
        }

        if (parentFolder && !(parentFolder instanceof randar.Project.Folder)) {
            throw new Error('Invalid parent folder');
        }

        // Generate a new ID if none is provided.
        if (typeof id === 'undefined') {
            id = 0;
            while (this.project.folders[id]) {
                id++;
            }
        }

        if (project.folders[id]) {
            throw new Error('Project already contains item with same ID');
        }

        this.id   = id;
        this.name = name;

        this.folders = [];
        this.items   = [];

        this.move(parentFolder);
        this.project.folders[id] = this;
    };

    /**
     * Moves a folder.
     */
    randar.Project.Folder.prototype.move = function(otherFolder) {
        if (this.parentFolder) {
            let idx = this.parentFolder.folders.indexOf(this);
            if (idx > -1) {
                this.parentFolder.folders.splice(idx, 1);
            }
            this.parentFolder = null;
        }

        if (otherFolder) {
            otherFolder.folders.push(this);
            this.parentFolder = otherFolder;
        }

        if (!this.parentFolder) {
            this.project.bins[this.id] = this;
        } else if (this.project.bins[this.id]) {
            delete this.project.bins[this.id];
        }
    };
};
