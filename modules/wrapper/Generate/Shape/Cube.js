module.exports = (randar) => {
    randar.generate.cube = function(width) {
        return randar.generate.cuboid(width, width, width);
    }
}
