const rgb  = ['r', 'g', 'b'];
const rgba = rgb.concat('a');

describe('Color', function() {
    describe('construction', function() {
        it('default constructs opaque black', function() {
            const color = randar.color();
            assert.equal(color.r(), 0);
            assert.equal(color.g(), 0);
            assert.equal(color.b(), 0);
            assert.equal(color.a(), 1);
        });

        it('constructs rgb arguments', function() {
            const color = randar.color(
                0.250980406999588,
                0.9882352948188782,
                0.3490196168422699
            );

            assert.equal(color.r(), 0.250980406999588);
            assert.equal(color.g(), 0.9882352948188782);
            assert.equal(color.b(), 0.3490196168422699);
        });

        it('constructs rgba arguments', function() {
            const color = randar.color(
                0.250980406999588,
                0.9882352948188782,
                0.3490196168422699,
                0.09803921729326248
            );

            assert.equal(color.r(), 0.250980406999588);
            assert.equal(color.g(), 0.9882352948188782);
            assert.equal(color.b(), 0.3490196168422699);
            assert.equal(color.a(), 0.09803921729326248);
        });

        it('refuses string arguments', function() {
            assert.throws(() => randar.color('0.1', '0.2', '0.3', '0.4'));
        });

        it('refuses one or two numeric arguments', function() {
            assert.throws(() => randar.color(0.75));
            assert.throws(() => randar.color(0.54, 0.29));
        });

        it('does not interpret 8-bit integers', function() {
            const color = randar.color(135, 49, 164, 255);
            
            for (channel of rgba) {
                assert.equal(color[channel](), 1);
            }
        });
    });

    describe('8-bit integers', function() {
        it('assign and retrieve within [0, 255]', function() {
            const color = randar.color();

            for (channel of rgba) {
                const fn = `${channel}Int`;
                color[fn](135);
                assert.equal(color[fn](), 135);
            }

            color.setInt(254, 253, 0, 255);
            assert.equal(color.rInt(), 254);
            assert.equal(color.gInt(), 253);
            assert.equal(color.bInt(), 0);
            assert.equal(color.aInt(), 255);
        });

        it('refuse being set out-of-range', function() {
            const color = randar.color();

            for (channel of rgba) {
                assert.throws(() => color[`${channel}Int`](256));
                assert.throws(() => color[`${channel}Int`](-1));
            }

            assert.throws(() => color.setInt(135, 135, 135, 300));
        });
    });

    describe('floats', function() {
        it('clamp within [0, 1]', function() {
            const color = randar.color();

            for (channel of rgba) {
                color[channel](1.3);
                assert.equal(color[channel](), 1);
            }

            for (channel of rgba) {
                color[channel](-2.75);
                assert.equal(color[channel](), 0);
            }

            color.set(7.69, 1000, 2047, 1.01);
            for (channel of rgba) {
                assert.equal(color[channel](), 1);
            }

            color.set(-7.69, -1000, -2047, -1.01);
            for (channel of rgba) {
                assert.equal(color[channel](), 0);
            }
        });
    });

    it('varies', function() {
        let color = randar.color(0.5, 0.5, 0.5);

        for (let i = 0; i < 1000; i++) {
            let varied = color.varied(randar.color());
            for (channel of rgb) {
                assert.equal(color[channel](), varied[channel]());
            }

            varied = color.varied(randar.color(0.2, 0.2, 0.2));
            for (channel of rgb) {
                let value = varied[channel]();
                assert(value >= 0.3 && value <= 0.7);
            }
        }
    });
});
