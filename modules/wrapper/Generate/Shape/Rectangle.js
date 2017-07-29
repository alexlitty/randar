module.exports = (randar) => {
    randar.generate.rectangle = function(width, height) {
        let geometry = randar.geometry();

        let wr = width / 2;
        let hr = height / 2;

        let topLeft     = randar.vector(-wr, -hr, 0);
        let topRight    = randar.vector(wr, -hr, 0);
        let bottomLeft  = randar.vector(-wr, hr, 0);
        let bottomRight = randar.vector(wr, hr, 0);

        geometry.append(randar.vertex(topLeft));
        geometry.append(randar.vertex(topRight));
        geometry.append(randar.vertex(bottomRight));

        geometry.append(randar.vertex(topLeft));
        geometry.append(randar.vertex(bottomRight));
        geometry.append(randar.vertex(bottomLeft));

        return geometry;
    }
}
