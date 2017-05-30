module.exports = (randar) => {
    /**
     * Adds a bin item to the system.
     */
    randar.Project.prototype.addBinItem = function(object, name, folder) {
        if (!object || !object.kind) {
            throw new Error('Incompatible object');
        }

        if (!folder) {
            throw new Error('Folder must be provided');
        }

        if (!name) {
            name = 'Untitled item';
        }

        let id = 0;
        while (this.binItems[id]) {
            id++;
        }

        this.binItems[id] = {
            kind   : object.kind(),
            object : object,
            name   : name,
            id     : id,

            depended : [],
            depends  : [],

            dirty : true
        };

        this.moveBinItem(this.binItems[id], folder);

        return this.binItems[id];
    };

    /**
     * Removes a bin item from the system.
     */
    randar.Project.prototype.removeBinItem = function(item) {
        if (!this.binItems[item.id]) {
            throw new Error('Bin item does not exist');
        }

        if (item.depended.length) {
            throw new Error('Other bin items depend on this item');
        }

        this.destroyBinItem(item);
        this.moveBinItem(item, null);
        delete this.binItems[item.id];
    }

    /**
     * Moves a bin item to another folder.
     */
    randar.Project.prototype.moveBinItem = function(item, folder) {
        if (item.folder) {
            let idx = item.folder.items.indexOf(item);
            if (idx > -1) {
                item.folder.items.splice(idx, 1);
            }
            item.folder = null;
        }

        if (folder) {
            folder.items.push(item);
            item.folder = folder;
        }
    }

    /**
     * Adds a bin item dependency.
     */
    randar.Project.prototype.binItemDepends = function(item, otherItem) {
        item.depends.push(otherItem);
        otherItem.depended.push(item);
    }

    /**
     * Require additional functionality.
     */
    require('./BinItemDirectory.js')(randar);
    require('./SaveBinItem.js')(randar);
    require('./LoadBinItem.js')(randar);
    require('./DestroyBinItem.js')(randar);
};
