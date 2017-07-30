module.exports = (randar) => {
    randar.generate.rectangle = function(width, height, palette) {
        palette = palette || randar.palette.Default;
        let geometry = randar.geometry();

        let wr = width / 2;
        let hr = height / 2;

        let topLeft     = randar.vector(-wr, -hr, 0);
        let topRight    = randar.vector(wr, -hr, 0);
        let bottomLeft  = randar.vector(-wr, hr, 0);
        let bottomRight = randar.vector(wr, hr, 0);

        let color = palette.sample();
        geometry.append(randar.vertex(topLeft, color));
        geometry.append(randar.vertex(topRight, color));
        geometry.append(randar.vertex(bottomRight, color));

        geometry.append(randar.vertex(topLeft, color));
        geometry.append(randar.vertex(bottomRight, color));
        geometry.append(randar.vertex(bottomLeft, color));

        return geometry;
    }
}
