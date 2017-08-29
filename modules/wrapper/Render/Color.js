const _ = require('underscore');

module.exports = (randar) => {
    randar.color = function(r, g, b, a) {
        if (arguments.length == 1 || arguments.length == 2) {
            throw new Error('Invalid construction arguments');
        }

        return new randar.Color(
            _.isUndefined(r) ? 0 : r,
            _.isUndefined(b) ? 0 : g,
            _.isUndefined(g) ? 0 : b,
            _.isUndefined(a) ? 1 : a
        );
    }
};
