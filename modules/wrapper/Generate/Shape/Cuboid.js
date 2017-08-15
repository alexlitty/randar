module.exports = (randar) => {
    randar.generate.cuboid = function(options) {
        let palette = options.palette || randar.palette.Default;
        let geometry = randar.geometry();

        let wr = options.width / 2;
        let hr = options.height / 2;
        let dr = options.depth / 2;

        let vertex = randar.vertex();

        let frontTopLeft     = vertex.withPosition(randar.vector(-wr, -hr, -dr));
        let frontTopRight    = vertex.withPosition(randar.vector(wr, -hr, -dr));
        let frontBottomLeft  = vertex.withPosition(randar.vector(-wr, hr, -dr));
        let frontBottomRight = vertex.withPosition(randar.vector(wr, hr, -dr));

        let backTopLeft      = vertex.withPosition(randar.vector(-wr, -hr, dr));
        let backTopRight     = vertex.withPosition(randar.vector(wr, -hr, dr));
        let backBottomLeft   = vertex.withPosition(randar.vector(-wr, hr, dr));
        let backBottomRight  = vertex.withPosition(randar.vector(wr, hr, dr));

        // Front face.
        let color = palette.sample();
        geometry.append(frontTopLeft.withColor(color));
        geometry.append(frontTopRight.withColor(color)); 
        geometry.append(frontBottomRight.withColor(color));

        geometry.append(frontTopLeft.withColor(color));
        geometry.append(frontBottomRight.withColor(color));
        geometry.append(frontBottomLeft.withColor(color));

        // Back face.
        color = palette.sample();
        geometry.append(backTopLeft.withColor(color));
        geometry.append(backTopRight.withColor(color));
        geometry.append(backBottomRight.withColor(color));

        geometry.append(backTopLeft.withColor(color));
        geometry.append(backBottomRight.withColor(color));
        geometry.append(backBottomLeft.withColor(color));

        // Left face.
        color = palette.sample();
        geometry.append(frontTopLeft.withColor(color));
        geometry.append(backTopLeft.withColor(color));
        geometry.append(backBottomLeft.withColor(color));

        geometry.append(frontTopLeft.withColor(color));
        geometry.append(backBottomLeft.withColor(color));
        geometry.append(frontBottomLeft.withColor(color));

        // Right face.
        color = palette.sample();
        geometry.append(frontTopRight.withColor(color));
        geometry.append(backTopRight.withColor(color));
        geometry.append(backBottomRight.withColor(color));

        geometry.append(frontTopRight.withColor(color));
        geometry.append(backBottomRight.withColor(color));
        geometry.append(frontBottomRight.withColor(color));

        // Top face.
        color = palette.sample();
        geometry.append(frontTopLeft.withColor(color));
        geometry.append(frontTopRight.withColor(color));
        geometry.append(backTopRight.withColor(color));
        
        geometry.append(frontTopLeft.withColor(color));
        geometry.append(backTopRight.withColor(color));
        geometry.append(backTopLeft.withColor(color));

        // Bottom face.
        color = palette.sample();
        geometry.append(frontBottomLeft.withColor(color));
        geometry.append(frontBottomRight.withColor(color));
        geometry.append(backBottomRight.withColor(color));
        
        geometry.append(frontBottomLeft.withColor(color));
        geometry.append(backBottomRight.withColor(color));
        geometry.append(backBottomLeft.withColor(color));

        return geometry;
    }
}
