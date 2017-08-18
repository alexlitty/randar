const _ = require('underscore');

module.exports = (randar) => {
    randar.generate.cuboid = function(options) {
        let palette = options.palette || randar.palette.Default;
        let geometry = randar.geometry();

        let frontTopLeft, frontTopRight, frontBottomLeft, frontBottomRight,
            backTopLeft, backTopRight, backBottomLeft, backBottomRight;

        if (options.frontTopLeft && options.frontTopRight && options.frontBottomLeft && options.frontBottomRight &&
            options.backTopLeft && options.backTopRight && options.backBottomLeft && options.backBottomRight)
        {
            frontTopLeft     = options.frontTopLeft;
            frontTopRight    = options.frontTopRight;
            frontBottomLeft  = options.frontBottomLeft;
            frontBottomRight = options.frontBottomRight;

            backTopLeft      = options.backTopLeft;
            backTopRight     = options.backTopRight;
            backBottomLeft   = options.backBottomLeft;
            backBottomRight  = options.backBottomRight;
        }

        else if (_.isNumber(options.width), _.isNumber(options.height), _.isNumber(options.depth)) {
            let wr = options.width / 2;
            let hr = options.height / 2;
            let dr = options.depth / 2;

            let vertex = randar.vertex();
            if (_.isNumber(options.joint)) {
                vertex = vertex.withJoint(options.joint);
            }

            frontTopLeft     = vertex.withPosition(randar.vector(-wr, -hr, -dr));
            frontTopRight    = vertex.withPosition(randar.vector(wr, -hr, -dr));
            frontBottomLeft  = vertex.withPosition(randar.vector(-wr, hr, -dr));
            frontBottomRight = vertex.withPosition(randar.vector(wr, hr, -dr));

            backTopLeft      = vertex.withPosition(randar.vector(-wr, -hr, dr));
            backTopRight     = vertex.withPosition(randar.vector(wr, -hr, dr));
            backBottomLeft   = vertex.withPosition(randar.vector(-wr, hr, dr));
            backBottomRight  = vertex.withPosition(randar.vector(wr, hr, dr));
        }

        else {
            throw new Error('Invalid generation options');
        }

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
