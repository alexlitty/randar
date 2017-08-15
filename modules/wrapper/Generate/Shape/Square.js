const _ = require('underscore');

module.exports = (randar) => {
    randar.generate.square = function(options) {
        return randar.generate.rectangle(_.extend(options, {
            height: options.width
        }));
    }
}
