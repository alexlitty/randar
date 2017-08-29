module.exports = (randar) => {
    randar.color = function() {
        return new (randar.Color.bind.apply(randar.Color, arguments));
    }
};
