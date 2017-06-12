const fs = require('fs');

module.exports = (randar) => {
    /**
     * An item in a Randar project.
     *
     * Items are wrappers that represent lower-level resources. They handle
     * resource saving, loading, and unloading as appropriate.
     */
    randar.Project.Item = function(folder, kind, name, id) {
        if (!folder || !(folder instanceof randar.Project.Folder)) {
            throw new Error('Project folder must be provided');
        }
        this.project = folder.project;

        if (typeof kind !== 'string') {
            throw new Error('Item kind must be provided as a string');
        }

        if (typeof name !== 'string') {
            throw new Error('Item name must be provided as a string');
        }

        // Generate a new ID if none is provided.
        if (typeof id === 'undefined') {
            id = 0;
            while (this.project.items[id]) {
                id++;
            }
        }

        if (this.project.items[id]) {
            throw new Error('Project already contains item with same ID');
        }

        this.kind = kind;
        this.name = name;
        this.id   = id;

        this.dirty = true;

        this.move(folder);
        this.project.items[id] = this;
    }

    /**
     * Retrieves the directory dedicated to this item.
     */
    randar.Project.Item.prototype.directory = function() {
        return this.project.directory().child(this.id+'');
    }

    /**
     * Sets or retrieves the object represented by an item.
     *
     * If the object is being retrieved, it is loaded into memory. This does not
     * necessarily initialize the resource. To save memory, the object can be
     * later unloaded while it isn't being used.
     */
    randar.Project.Item.prototype.object = function(newObject) {
        if (arguments.length) {
            if (!newObject.kind || newObject.kind() !== this.kind) {
                throw new Error('Incompatible object kind');
            }
            this._object = newObject;
        }

        else {
            if (!this.isLoaded()) {
                this.load();
            }
            return this._object;
        }
    };

    /**
     * Destroys the item on disk, if applicable.
     */
    randar.Project.Item.prototype.destroy = function() {
        if (!this.project.onDisk) {
            return;
        }

        try {
            randar.removeDirectory(this.directory());
        } catch (e) { }
    };

    /**
     * Saves the item to disk.
     */
    randar.Project.Item.prototype.save = function() {
        if (!this.dirty || !this.isLoaded()) {
            return;
        }

        if (this.kind === 'geometry') {
            this.object().save(this.directory().child('item.rGeometry'));
        }

        else if (this.kind === 'image') {
            this.object().save(this.directory().child('item.png'));
        }

        else {
            throw new Error(`Saving "${item.kind}" not implemented`);
        }

        this.dirty = false;
    };

    /**
     * Loads the item into memory from disk.
     *
     * If the item does not exist on disk, an empty resource is loaded.
     */
    randar.Project.Item.prototype.load = function() {
        this.unload();

        if (this.kind === 'geometry') {
            this.object(randar.geometry());

            if (this.isOnDisk()) {
                this.object().load(this.directory().child('item.rGeometry'));
            }
        }

        else if (this.kind === 'image') {
            this.object(randar.image());

            if (this.isOnDisk()) {
                this.object().load(this.directory().child('item.png'));
            }
        }

        else {
            throw new Error(`Loading "${item.kind}" not implemented`);
        }

        this.dirty = !this.isOnDisk();
    };

    /**
     * Unloads the item from memory.
     */
    randar.Project.Item.prototype.unload = function() {
        this._object = null;
        this.dirty   = false;
    };

    /**
     * Whether the item is loaded into memory.
     */
    randar.Project.Item.prototype.isLoaded = function() {
        return !!this._object;
    };

    /**
     * Whether the item is on disk.
     */
    randar.Project.Item.prototype.isOnDisk = function() {
        return fs.existsSync(this.directory().toString());
    };

    /**
     * Moves the item to a new folder.
     *
     * If no folder is specified, it is simply removed from its current folder.
     */
    randar.Project.Item.prototype.move = function(newFolder) {
        // Remove from old folder.
        if (this.folder) {
            let idx = this.folder.items.indexOf(this);

            if (idx > -1) {
                this.folder.items.splice(idx, 1);
            }

            this.folder = null;
        }

        // Add to new folder.
        if (newFolder) {
            this.folder = newFolder;
            this.folder.items.push(this);
        }
    };
};
