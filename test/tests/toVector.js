describe('toVector', function() {
    it('converts from numbers', function() {
        let vector = randar.toVector({
            x : 100,
            y : 200,
            z : 300
        });

        assert.equal(vector.x, 100);
        assert.equal(vector.y, 200);
        assert.equal(vector.z, 300);
    });

    it('converts from strings', function() {
        let vector = randar.toVector({
            x : '400',
            y : '500',
            z : '600'
        });

        assert.equal(vector.x, 400);
        assert.equal(vector.y, 500);
        assert.equal(vector.z, 600);
    });

    it('refuses ill-formed object', function() {
        assert.throws(() => randar.toVector({
            x : 'test',
            y : 'foobar',
            z : { invalid: value }
        }));
    });
});
