const assert  = require('assert');
const adapter = require('../../modules/adapter');

function constructDefault(routine) {
    const gpu  = new adapter.Gpu();
    const dims = gpu.defaultFramebufferDimensions();
    const fb   = new adapter.Framebuffer(gpu, dims);

    assert(fb.getWidth() > 0 && fb.getHeight() > 0);

    if (routine) {
        routine(gpu, dims, fb);
    }

    return fb;
}

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
    describe('construction', function() {
        it('default constructs to default framebuffer', function() {
            constructDefault(function(gpu, dims, fb) {
                assert(fb.isDefault());
                assert(fb.getWidth(), dims.getWidth());
                assert(fb.getHeight(), dims.getHeight());
            });
        });
    });

    describe('usage', function() {
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
    });
});