module.exports = (randar) => {
    randar.palette.Varying = function(color, variance) {
        this.color    = color;
        this.variance = variance;
    }

    randar.palette.varying = function(color, variance) {
        return (new randar.palette.Varying(color, variance));
    }

    randar.palette.Varying.prototype.sample = function() {
        let color = randar.color(
            this.color.r(),
            this.color.g(),
            this.color.b(),
            this.color.a()
        );

        for (let channel of ['r', 'g', 'b', 'a']) {
            color[channel](
                randar.randomFloat(
                    Math.max(0, this.color[channel]() - this.variance[channel]()),
                    Math.min(1, this.color[channel]() + this.variance[channel]())
                )
            );
        }

        return color;
    }
}
