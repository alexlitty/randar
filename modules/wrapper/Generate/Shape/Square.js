module.exports = (randar) => {
    randar.generate.square = function(geometry, width) {
        randar.generate.rectangle(geometry, width, width);
    }
}
