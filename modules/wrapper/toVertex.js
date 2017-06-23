module.exports = (randar) => {
    randar.toVertex = function(obj) {
        if (!obj) {
            throw new Error('Invalid conversion to vertex');
        }

        let vertex = randar.vertex();

        if (obj.position) {
            vertex.position = randar.toVector(obj.position);
        }

        if (obj.color) {
            vertex.color = randar.toColor(obj.color);
        }

        if (obj.normal) {
            vertex.normal = randar.toVector(obj.normal);
        }

        if (typeof obj.textureId !== 'undefined') {
            vertex.textureId = obj.textureId;
        }

        if (obj.textureCoordinate) {
            vertex.textureCoordinate = randar.toVector(obj.textureCoordinate);
        }

        if (obj.jointWeights) {
            // @@@
        }
    };
};
