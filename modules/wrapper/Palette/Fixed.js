module.exports = (randar) => {
    randar.palette.Fixed = function(colors) {
        if (!colors.length) {
            throw new Error('Colors must be provided to fixed palette');
        }

        this.colors = colors;
    }

    randar.palette.fixed = function(colors) {
        return (new randar.palette.Fixed(colors));
    }

    randar.palette.Fixed.prototype.sample = function() {
        if (!this.colors.length) {
            throw new Error('No colors available in the palette');
        }

        return this.colors[randar.randomInt_uint32(0, this.colors.length - 1)];
    }
}
