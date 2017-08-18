const _ = require('underscore');

module.exports = (randar) => {
    randar.generate.rectangle = function(options) {
        let palette = options.palette || randar.palette.Default;
        let geometry = randar.geometry();

        let topLeft, topRight, bottomLeft, bottomRight;

        if (options.topLeft && options.topRight && options.bottomLeft && options.bottomRight) {
            topLeft     = options.topLeft;
            topRight    = options.topRight;
            bottomLeft  = options.bottomLeft;
            bottomRight = options.bottomRight;
        }

        else if (_.isNumber(options.width) && _.isNumber(options.height)) {
            let wr = options.width / 2;
            let hr = options.height / 2;

            topLeft     = randar.vector(-wr, -hr, 0);
            topRight    = randar.vector(wr, -hr, 0);
            bottomLeft  = randar.vector(-wr, hr, 0);
            bottomRight = randar.vector(wr, hr, 0);
        }

        else {
            throw new Error('Invalid generation options');
        }

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
