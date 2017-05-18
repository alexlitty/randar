module.exports = (randar) => {
    randar.vertex = function() {
        return new (Function.prototype.bind.apply(randar.Vertex, arguments));
    }
};
