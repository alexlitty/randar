const assert  = require('assert');
const adapter = require('../../modules/adapter');

function assertDims(texture, width, height) {
    assert.equal(texture.getWidth(), width);
    assert.equal(texture.getHeight(), height);
};

const ctx = new adapter.GraphicsContext();

describe.only('Texture', function() {
    it('constructs rgba by default', function() {
        const texture = new adapter.Texture(ctx, 64, 64);
        assert.equal(texture.type, 'rgba');
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
                    new adapter.Texture(ctx, dim.x, dim.y),
                    dim.x,
                    dim.y
                );
            }
        });
    });
});
