module.exports = (randar) => {
    randar.toColor = function(obj) {
        if (!obj) {
            throw new Error('Invalid conversion to color');
        }

        let color = randar.color();
        for (let channel of ['r', 'g', 'b', 'a']) {
            if (obj[channel]) {
                color[channel](obj[channel]);
            }

            else if (obj[channel + 'Int']) {
                color[channel + 'Int'](obj[channel + 'Int']);
            }

            else if (channel === 'a') {
                color.a(1);
            }

            else {
                color[channel](0);
            }
        }

        return color;
    };
};
