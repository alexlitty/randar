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

describe.only('Framebuffer', function() {
    describe('window', function() {
        it('constructs with window', function() {
            let ctx = new adapter.GraphicsContext();
            let win = new adapter.Window(ctx, 600, 480);
            let fb  = new adapter.Framebuffer(win);
            assert.equal(fb.getGlName(), 0);
        });

        it('refuses attachments', function() {
            let ctx = new adapter.GraphicsContext();
            let win = new adapter.Window(ctx, 800, 600);
            let fb  = new adapter.Framebuffer(win);

            let texture = new adapter.Texture(ctx, 800, 600, 'rgba');
            assert.throws(() => fb.attach(texture));
        });

        //it('multiple constructions affect same window', function() {
        //});
    });

    describe('off-screen', function() {
        it('constructs with context', function() {
            let ctx = new adapter.GraphicsContext();
            let fb  = new adapter.Framebuffer(ctx);
            assert.notEqual(fb.getGlName(), 0);
        });

        it('constructs unique gl names', function() {
            let ctx = new adapter.GraphicsContext();
            let fb1 = new adapter.Framebuffer(ctx);
            let fb2 = new adapter.Framebuffer(ctx);

            assert.notEqual(fb1.getGlName(), 0);
            assert.notEqual(fb2.getGlName(), 0);
            assert.notEqual(fb1.getGlName(), fb2.getGlName());
        });

        it('initializes after attachment', function() {
            let ctx = new adapter.GraphicsContext();
            let fb  = new adapter.Framebuffer(ctx);

            let texture = new adapter.Texture(ctx, 64, 64, 'rgba');
            console.log('???', texture.type);
            fb.attach(texture);
            console.log('???');

            assert.notEqual(fb.getGlName(), 0);
            assert.equal(fb.getWidth(), texture.getWidth());
            assert.equal(fb.getHeight(), texture.getHeight());
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
