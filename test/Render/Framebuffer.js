const assert  = require('assert');
const adapter = require('../../modules/adapter');
const ctx     = require('../../modules/adapter');

function assertColor(color, expectedColor) {
    assert.equal(color.r(), expectedColor.r());
    assert.equal(color.g(), expectedColor.g());
    assert.equal(color.b(), expectedColor.b());
    assert.equal(color.a(), expectedColor.a());
}

function assertCleared(gpu, fb, expectedColor) {
    const image = new adapter.Image();
    gpu.read(fb, image);

    assert(image.hasDimensions());
    for (var x = 0; x < image.getWidth(); x++) {
        for (var y = 0; y < image.getHeight(); y++) {
            assertColor(image.getPixel(x, y), expectedColor);
        }
    }
}

describe('Framebuffer', function() {
    describe('window', function() {
        it('constructs with window', function() {
            let ctx = new adapter.GraphicsContext();
            let win = new adapter.Window(ctx, 600, 480);
            let fb  = new adapter.Framebuffer(win);
        });
    });

    /*describe('usage', function() {
        it('clears with no argument', function() {
            constructDefault(function(gpu, dims, fb) {
                fb.clear();
                assertCleared(gpu, fb, new adapter.Color());
            });
        });

        it('clears with a color argument', function() {
            constructDefault(function(gpu, dims, fb) {
                const colors = [
                    new adapter.Color(1, 1, 1, 1),
                    new adapter.Color(0, 0, 1, 0)
                ];

                for (color of colors) {
                    fb.clear(color);
                    assertCleared(gpu, fb, color);
                }
            });
        });
    });*/
});
