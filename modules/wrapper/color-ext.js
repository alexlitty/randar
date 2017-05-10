/**
 * Extends Color functionality.
 */
module.exports = (randar) => {
    /**
     * Available color channels and their human-friendly names.
     */
    randar.Color.channels = {
        'r' : 'red',
        'g' : 'green',
        'b' : 'blue',
        'a' : 'alpha'
    };
    Object.freeze(randar.Color.channels);

    /**
     * Compares this color with another color.
     *
     * If the channel values are not primitively equivalent, they are compared
     * up to the optionally specified precision. Default precision is 5.
     */
    randar.Color.prototype.equals = function(other, precision = 5) {
        for (let channel in randar.Color.channels) {
            let t = this[channel]();
            let o = other[channel]();

            // Perform the fastest comparison first.
            if (t === o) {
                continue;
            }

            // Perform a precise comparison only if necessary.
            if (t.toFixed(precision) === o.toFixed(precision)) {
                continue;
            }

            return false;
        }

        return true;
    };
};
