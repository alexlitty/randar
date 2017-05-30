module.exports = (randar) => {
    randar.Project.prototype.loadBinItem = function(item) {
        let itemDirectory = this.binItemDirectory(item);

        if (!item.kind) {
            throw new Error('Incompatible object');
        }

        if (item.object) {
            item.object = null;
        }

        if (item.kind === 'geometry') {
            item.object = randar.geometry();
            item.object.load(itemDirectory.child('item.rGeometry'));
        }

        else if (item.kind === 'image') {
            item.object = randar.image(itemDirectory.child('item.png'));
        }

        else {
            throw new Error(`Loading "${item.kind}" not implemented`);
        }
    };
};
