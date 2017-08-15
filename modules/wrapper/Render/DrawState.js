const _ = require('underscore');

module.exports = (randar) => {
    randar.drawState = function(state) {
        let ds = new randar.DrawState();

        if (typeof state === 'undefined') {
            return ds;
        }

        if (typeof state !== 'object') {
            throw new Error('Invalid draw state options');
        }

        _.each(state, (value, key) => {
            if (key === 'transform') {
                ds.transform = value;
            }

            else if (key === 'skeleton') {
                ds.skeleton = value;
            }

            else if (key === 'textures') {
                ds.textures = value;
            }

            else if (key === 'lights') {
                ds.lights = value;
            }

            else if (key === 'program') {
                ds.program = value;
            }

            else {
                throw new Error(`Unknown draw state property: ${key}`);
            }
        });

        return ds;
    };
};
