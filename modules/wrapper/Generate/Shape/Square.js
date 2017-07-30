module.exports = (randar) => {
    randar.generate.square = function(width, palette) {
        return randar.generate.rectangle(width, width, palette);
    }
}
