module.exports = (randar) => {
    randar.generate.cube = function(width, palette) {
        return randar.generate.cuboid(width, width, width, palette);
    }
}
