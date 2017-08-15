const _ = require('underscore');

module.exports = (randar) => {
    randar.generate.cube = function(options) {
        return randar.generate.cuboid(_.extend(options, {
            height : options.width,
            depth  : options.width
        }));
    }
}
