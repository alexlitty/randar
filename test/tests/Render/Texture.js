function assertDims(texture, width, height) {
    assert.equal(texture.getWidth(), width);
    assert.equal(texture.getHeight(), height);
};

describe('Texture', function() {
    it('constructs rgba by default', function() {
        const texture = new randar.Texture(64, 64);
        assert.equal(texture.type, 'rgba');
    });

    it('refuses invalid type construction', function() {
        assert.throws(() => new randar.Texture(64, 64, 'invalid'));
    });

    describe('rgba', function() {
        it('constructs with correct dimensions', function() {
            const dims = [
                { x: 64, y: 64 },
                { x: 128, y: 128 },
                { x: 1024, y: 1024 }
            ];

            for (dim of dims) {
                assertDims(
                    new randar.Texture(dim.x, dim.y, 'rgba'),
                    dim.x,
                    dim.y
                );
            }
        });

        it('refuses construction with invalid dimensions', function() {
            assert.throws(() => new randar.Texture(-32, 32, 'rgba'));
        });

        it('resizes with correct dimensions', function() {
            const dims = [
                { x: 64, y: 64 },
                { x: 128, y: 128 },
                { x: 1024, y: 1024 }
            ];

            for (dim of dims) {
                let texture = new randar.Texture(2, 2, 'rgba');

                assert.doesNotThrow(() => texture.resize(dim.x, dim.y));
                assertDims(texture, dim.x, dim.y);
            }
        });

        it('refuses resizing with invalid dimensions', function() {
            let texture = new randar.Texture(32, 32, 'rgba');
            assert.throws(() => texture.resize(-32, 32));
        });
    });
});
