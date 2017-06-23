describe('toColor', function() {
    it('rejects bad input', function() {
        assert.throws(() => randar.toColor());
    });

    it('defaults to opaque black', function() {
        let color = randar.toColor({ });

        assert.equal(color.r(), 0);
        assert.equal(color.g(), 0);
        assert.equal(color.b(), 0);
        assert.equal(color.a(), 1);
    });

    it('converts from floats', function() {
        let color = randar.toColor({
            r: 0.5,
            g: 0.6,
            b: 0.7,
            a: 0.8
        });

        assert.equal(color.r().toFixed(1), 0.5);
        assert.equal(color.g().toFixed(1), 0.6);
        assert.equal(color.b().toFixed(1), 0.7);
        assert.equal(color.a().toFixed(1), 0.8);
    });

    it('converts from integers', function() {
        let color = randar.toColor({
            rInt: 150,
            gInt: 160,
            bInt: 170,
            aInt: 180
        });

        assert.equal(color.r().toFixed(1), (150 / 255).toFixed(1));
        assert.equal(color.g().toFixed(1), (160 / 255).toFixed(1));
        assert.equal(color.b().toFixed(1), (170 / 255).toFixed(1));
        assert.equal(color.a().toFixed(1), (180 / 255).toFixed(1));
    });
});
