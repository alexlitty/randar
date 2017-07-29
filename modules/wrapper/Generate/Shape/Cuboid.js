module.exports = (randar) => {
    randar.generate.cuboid = function(width, height, depth) {
        let geometry = randar.geometry();

        let wr = width / 2;
        let hr = height / 2;
        let dr = depth / 2;

        let frontTopLeft     = randar.vertex(randar.vector(-wr, -hr, -dr));
        let frontTopRight    = randar.vertex(randar.vector(wr, -hr, -dr));
        let frontBottomLeft  = randar.vertex(randar.vector(-wr, hr, -dr));
        let frontBottomRight = randar.vertex(randar.vector(wr, hr, -dr));

        let backTopLeft      = randar.vertex(randar.vector(-wr, -hr, dr));
        let backTopRight     = randar.vertex(randar.vector(wr, -hr, dr));
        let backBottomLeft   = randar.vertex(randar.vector(-wr, hr, dr));
        let backBottomRight  = randar.vertex(randar.vector(wr, hr, dr));

        // Front face.
        geometry.append(frontTopLeft);
        geometry.append(frontTopRight);
        geometry.append(frontBottomRight);

        geometry.append(frontTopLeft);
        geometry.append(frontBottomRight);
        geometry.append(frontBottomLeft);

        // Back face.
        geometry.append(backTopLeft);
        geometry.append(backTopRight);
        geometry.append(backBottomRight);

        geometry.append(backTopLeft);
        geometry.append(backBottomRight);
        geometry.append(backBottomLeft);

        // Left face.
        geometry.append(frontTopLeft);
        geometry.append(backTopLeft);
        geometry.append(backBottomLeft);

        geometry.append(frontTopLeft);
        geometry.append(backBottomLeft);
        geometry.append(frontBottomLeft);

        // Right face.
        geometry.append(frontTopRight);
        geometry.append(backTopRight);
        geometry.append(backBottomRight);

        geometry.append(frontTopRight);
        geometry.append(backBottomRight);
        geometry.append(frontBottomRight);

        // Top face.
        geometry.append(frontTopLeft);
        geometry.append(frontTopRight);
        geometry.append(backTopRight);
        
        geometry.append(frontTopLeft);
        geometry.append(backTopRight);
        geometry.append(backTopLeft);

        // Bottom face.
        geometry.append(frontBottomLeft);
        geometry.append(frontBottomRight);
        geometry.append(backBottomRight);
        
        geometry.append(frontBottomLeft);
        geometry.append(backBottomRight);
        geometry.append(backBottomLeft);

        return geometry;
    }
}
