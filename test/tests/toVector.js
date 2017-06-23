describe('toVector', function() {
    it('converts to vector3 from numbers', function() {
        let vector = randar.toVector({
            x : 100,
            y : 200,
            z : 300
        });

        assert.equal(vector.x, 100);
        assert.equal(vector.y, 200);
        assert.equal(vector.z, 300);
    });

    it('converts to vector3 from strings', function() {
        let vector = randar.toVector({
            x : '400',
            y : '500',
            z : '600'
        });

        assert.equal(vector.x, 400);
        assert.equal(vector.y, 500);
        assert.equal(vector.z, 600);
    });

    it('converts to vector2 from numbers', function() {
        let vector = randar.toVector({
            u : '0.5',
            v : '0.6'
        });

        assert.equal(vector.u().toFixed(1), 0.5);
        assert.equal(vector.v().toFixed(1), 0.6);
    });

    it('converts to vector2 from strings', function() {
        let vector = randar.toVector({
            u : 0.7,
            v : 0.8
        });

        assert.equal(vector.u().toFixed(1), 0.7);
        assert.equal(vector.v().toFixed(1), 0.8);
    });

    it('refuses ill-formed object', function() {
        assert.throws(() => randar.toVector({
            x : 'test',
            y : 'foobar',
            z : { invalid: value }
        }));
    });
});
