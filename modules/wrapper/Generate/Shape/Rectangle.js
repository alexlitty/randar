module.exports = (randar) => {
    randar.generate.rectangle = function(geometry, width, height) {
        if (width < 0) {
            width = -1 * width;
        }

        if (height < 0) {
            height = -1 * height;
        }

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
    }
}
