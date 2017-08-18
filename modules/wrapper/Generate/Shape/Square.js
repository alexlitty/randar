const _ = require('underscore');

module.exports = (randar) => {
    randar.generate.square = function(options) {
        if (_.isNumber(options.width)) {
            options.height = options.width;
        }

        return randar.generate.rectangle(options);
    }
}
