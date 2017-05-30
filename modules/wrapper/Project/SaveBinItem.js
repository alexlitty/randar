module.exports = (randar) => {
    randar.Project.prototype.saveBinItem = function(item) {
        if (!item.dirty) {
            return;
        }

        let itemDirectory = this.binItemDirectory();

        // Sanity check.
        if (!item.object) {
            throw new Error('Bin item has no object');
        }

        if (!item.kind) {
            throw new Error('Bin item holds incompatible object');
        }

        // Save item.
        if (item.kind === 'geometry') {
            item.object.save(itemDirectory.child('item.rGeometry'));
        }

        else if (item.kind === 'image') {
            item.object.save(itemDirectory.child('item.png'));
        }

        else {
            throw new Error(`Saving "${item.kind}" not implemented`);
        }
    };
};
