module.exports = (randar) => {
    randar.transform = function() {
        return new randar.Transform(...arguments);
    }
};
