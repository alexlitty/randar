module.exports = (randar) => {
    randar.generate.cuboid = function(width, height, depth, palette) {
        palette = palette || randar.palette.Default;
        let geometry = randar.geometry();

        let wr = width / 2;
        let hr = height / 2;
        let dr = depth / 2;

        let frontTopLeft     = randar.vector(-wr, -hr, -dr);
        let frontTopRight    = randar.vector(wr, -hr, -dr);
        let frontBottomLeft  = randar.vector(-wr, hr, -dr);
        let frontBottomRight = randar.vector(wr, hr, -dr);

        let backTopLeft      = randar.vector(-wr, -hr, dr);
        let backTopRight     = randar.vector(wr, -hr, dr);
        let backBottomLeft   = randar.vector(-wr, hr, dr);
        let backBottomRight  = randar.vector(wr, hr, dr);

        // Front face.
        let color = palette.sample();
        geometry.append(randar.vertex(frontTopLeft, color));
        geometry.append(randar.vertex(frontTopRight, color)); 
        geometry.append(randar.vertex(frontBottomRight, color));

        geometry.append(randar.vertex(frontTopLeft, color));
        geometry.append(randar.vertex(frontBottomRight, color));
        geometry.append(randar.vertex(frontBottomLeft, color));

        // Back face.
        color = palette.sample();
        geometry.append(randar.vertex(backTopLeft, color));
        geometry.append(randar.vertex(backTopRight, color));
        geometry.append(randar.vertex(backBottomRight, color));

        geometry.append(randar.vertex(backTopLeft, color));
        geometry.append(randar.vertex(backBottomRight, color));
        geometry.append(randar.vertex(backBottomLeft, color));

        // Left face.
        color = palette.sample();
        geometry.append(randar.vertex(frontTopLeft, color));
        geometry.append(randar.vertex(backTopLeft, color));
        geometry.append(randar.vertex(backBottomLeft, color));

        geometry.append(randar.vertex(frontTopLeft, color));
        geometry.append(randar.vertex(backBottomLeft, color));
        geometry.append(randar.vertex(frontBottomLeft, color));

        // Right face.
        color = palette.sample();
        geometry.append(randar.vertex(frontTopRight, color));
        geometry.append(randar.vertex(backTopRight, color));
        geometry.append(randar.vertex(backBottomRight, color));

        geometry.append(randar.vertex(frontTopRight, color));
        geometry.append(randar.vertex(backBottomRight, color));
        geometry.append(randar.vertex(frontBottomRight, color));

        // Top face.
        color = palette.sample();
        geometry.append(randar.vertex(frontTopLeft, color));
        geometry.append(randar.vertex(frontTopRight, color));
        geometry.append(randar.vertex(backTopRight, color));
        
        geometry.append(randar.vertex(frontTopLeft, color));
        geometry.append(randar.vertex(backTopRight, color));
        geometry.append(randar.vertex(backTopLeft, color));

        // Bottom face.
        color = palette.sample();
        geometry.append(randar.vertex(frontBottomLeft, color));
        geometry.append(randar.vertex(frontBottomRight, color));
        geometry.append(randar.vertex(backBottomRight, color));
        
        geometry.append(randar.vertex(frontBottomLeft, color));
        geometry.append(randar.vertex(backBottomRight, color));
        geometry.append(randar.vertex(backBottomLeft, color));

        return geometry;
    }
}
