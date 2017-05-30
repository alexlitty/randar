module.exports = (randar) => {
    randar.Project.prototype.binItemDirectory = function(item) {
        if (!item || !item.id) {
            throw new Error('Corrupted item:', item);
        }
        return this.directory().child(item.id);
    }
};
