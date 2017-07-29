module.exports = (randar) => {
    randar.generate.square = function(width) {
        return randar.generate.rectangle(width, width);
    }
}
