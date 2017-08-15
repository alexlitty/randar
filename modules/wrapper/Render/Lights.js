module.exports = (randar) => {
    randar.lights = function() {
        return new randar.LightCollection();
    };
};
