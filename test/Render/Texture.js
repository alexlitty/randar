function assertDims(texture, width, height) {
    assert.equal(texture.getWidth(), width);
    assert.equal(texture.getHeight(), height);
};

describe('Texture', function() {
    let ctx;

    before(function() {
        ctx = new adapter.GraphicsContext();
    });

    it('constructs rgba by default', function() {
        const texture = new adapter.Texture(ctx, 64, 64);
        assert.equal(texture.type, 'rgba');
    });

    it('refuses invalid type construction', function() {
        assert.throws(() => new adapter.Texture(ctx, 64, 64, 'invalid'));
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
                    new adapter.Texture(ctx, dim.x, dim.y, 'rgba'),
                    dim.x,
                    dim.y
                );
            }
        });

        it('refuses construction with invalid dimensions', function() {
            assert.throws(() => new adapter.Texture(ctx, -32, 32, 'rgba'));
            assert.throws(() => new adapter.Texture(ctx, 5000, 5000, 'rgba'));
        });

        it('resizes with correct dimensions', function() {
            const dims = [
                { x: 64, y: 64 },
                { x: 128, y: 128 },
                { x: 1024, y: 1024 }
            ];

            for (dim of dims) {
                let texture = new adapter.Texture(ctx, 2, 2, 'rgba');

                assert.doesNotThrow(() => texture.resize(dim.x, dim.y));
                assertDims(texture, dim.x, dim.y);
            }
        });

        it('refuses resizing with invalid dimensions', function() {
            let texture = new adapter.Texture(ctx, 32, 32, 'rgba');
            assert.throws(() => texture.resize(-32, 32));
            assert.throws(() => texture.resize(5000, 5000));
        });
    });
});
