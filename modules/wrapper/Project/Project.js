module.exports = (randar) => {
    /**
     * A Randar Project, in all its glory.
     *
     * Every project, at its core, simply has items and folders. Folders are
     * used by the UI to organize items; They serve absolutely no functionality
     * otherwise.
     *
     * "Bins" are just folders without a parent. Items are wrappers for lower
     * level resources.
     *
     * Project directories default to the current working directory.
     */
    randar.Project = function(dir) {
        this.clear();
        if (dir) {
            this.load(dir);
        }
    };

    randar.project = function(dir) {
        return new randar.Project(dir);
    };

    /**
     * Sets or retrieves the project directory.
     */
    randar.Project.prototype.directory = function(newDirectory) {
        if (!arguments.length) {
            return this._directory;
        } else {
            if (this.onDisk) {
                throw new Error('Cannot move project that exists on disk');
            }
            this._directory = randar.path(newDirectory);
        }
    }

    /**
     * Clears the project.
     */
    randar.Project.prototype.clear = function() {
        this.bins    = {};
        this.folders = {};
        this.items   = {};

        this.onDisk     = false;
        this._directory = randar.path();
    }

    /**
     * Saves the project.
     */
    randar.Project.prototype.save = function() {
        let json = {
            name    : this.name,
            folders : {},
            items   : {}
        };

        for (let folderId in this.folders) {
            let folder = this.folders[folderId];

            json.folders[folderId] = {
                name         : folder.name,
                parentFolder : folder.parentFolder,

                folders : folder.folders.map((folder) => folder.id)
            };
        }

        for (let itemId in this.items) {
            let item = this.items[itemId];

            json.items[itemId] = {
                kind   : item.kind,
                name   : item.name,
                folder : item.folder.id
            };

            item.save();
        }

        fs.writeFileSync(
            this.directory().child('project.json').toString(),
            JSON.stringify(json)
        );

        this.onDisk = true;
    };

    /**
     * Loads the project.
     */
    randar.Project.prototype.load = function(dir) {
        this.clear();
        this.directory(dir);

        let json = JSON.parse(
            fs.readFileSync(this.directory().child('project.json').toString())
        );

        // Project information.
        this.name = json.name;

        // Import folders.
        for (let folderId in json.folders) {
            let folder = json.folders[folderId];
            this.newFolder(folder.name, null, folderId);
        }

        // Organize folders.
        for (let folderId in json.folders) {
            let folder = json.folders[folderId];

            if (folder.parentFolder) {
                let parentFolder = this.folders[folder.parentFolder];

                if (!parentFolder) {
                    throw new Error('Corrupted folder structure');
                }

                this.folders[folderId].move(parentFolder);
            }
        }

        // Import items.
        for (let itemId in json.items) {
            let item = json.items[itemId];

            if (!this.folders[item.folder]) {
                throw new Error('Corrupted item owner');
            }

            this.newItem(this.folders[item.folder], item.kind, item.name, itemId);
        }

        this.onDisk = true;
    }

    /**
     * Adds a bin to the project.
     *
     * ID generated if not provided.
     */
    randar.Project.prototype.newBin = function(name, id) {
        return (new randar.Project.Folder(this, name, null, id));
    };

    /**
     * Adds a folder to the project.
     *
     * ID generated if not provided.
     */
    randar.Project.prototype.newFolder = function(name, parentFolder, id) {
        return (new randar.Project.Folder(this, name, parentFolder, id));
    };

    /**
     * Adds an item to the project.
     *
     * ID generated if not provided.
     */
    randar.Project.prototype.newItem = function(folder, kind, name, id) {
        return (new randar.Project.Item(folder, kind, name, id));
    };

    /**
     * Removes an entity from the project and from disk, if applicable.
     */
    randar.Project.prototype.remove = function(entity) {
        if (entity instanceof randar.Project.Folder) {
            let folder = entity;

            for (let subfolder of folder.folders) {
                this.remove(subfolder);
            }

            for (let item of folder.items) {
                this.remove(item);
            }

            folder.move(null);
            delete this.bins[folder.id];
            delete this.folders[folder.id];
        }

        else if (entity instanceof randar.Project.Item) {
            let item = entity;

            item.move(null);
            item.unload();
            if (this.onDisk) {
                item.destroy();
            }

            delete this.items[item.id];
        }
    };

    /**
     * Whether the project has any bins.
     */
    randar.Project.prototype.hasBins = function() {
        return !!Object.keys(this.bins).length;
    };

    /**
     * Require folder and item functionality.
     */
    require('./Folder.js')(randar);
    require('./Item.js')(randar);
};
