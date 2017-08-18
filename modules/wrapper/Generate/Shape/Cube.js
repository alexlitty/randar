const _ = require('underscore');

module.exports = (randar) => {
    randar.generate.cube = function(options) {
        if (_.isNumber(options.width)) {
            options.height = options.depth = options.width;
        }

        return randar.generate.cuboid(options);
    }
}
