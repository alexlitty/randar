function assertColor(color, expectedColor, msg) {
    assert.equal(color.r(), expectedColor.r(), msg); 
    assert.equal(color.g(), expectedColor.g(), msg);
    assert.equal(color.b(), expectedColor.b(), msg);
    assert.equal(color.a(), expectedColor.a(), msg);
}

function assertCleared(fb, expectedColor) {
    let image = new adapter.Image();
    fb.read(image);

    image.layout(adapter.Image.LAYOUT_NORMAL);
    assert(image.hasDimensions());
    assert.equal(image.getWidth(), fb.getWidth());
    assert.equal(image.getHeight(), fb.getHeight());
    for (var x = 0; x < image.getWidth(); x++) {
        for (var y = 0; y < image.getHeight(); y++) {
            assertColor(
                image.getPixel(x, y),
                expectedColor,
                `Pixel (${x}, ${y}) does not match expected color`
            );
        }
    }
}

describe.only('Framebuffer', function() {
    describe('window', function() {
        let ctx;
        
        beforeEach(function() {
            ctx = new adapter.GraphicsContext();
        });

        afterEach(function() {
            ctx = null;
        });

        it('constructs with window', function() {
            let win = new adapter.Window(ctx, 600, 480);
            let fb  = new adapter.Framebuffer(win);
            assert.equal(fb.getGlName(), 0);
        });

        it('refuses attachments', function() {
            let win = new adapter.Window(ctx, 800, 600);
            let fb  = new adapter.Framebuffer(win);

            let texture = ctx.texture(ctx, 800, 600, 'rgba');
            assert.throws(() => fb.attach(texture));
        });

        it('clears with correct color', function() {
            this.timeout(20000);
            let win = new adapter.Window(ctx, 800, 600);
            let fb  = new adapter.Framebuffer(win);
            const color = new adapter.Color(
                0.250980406999588,
                0.7490196228027344,
                0.2980392277240753
            );

            fb.clear(color);
            assertCleared(fb, color);
        });

        it('multiple constructions affect same window', function() {
            //let fb1 = new adapter.Framebuffer(win);
        });
    });

    describe('off-screen', function() {
        it('constructs with context', function() {
            let ctx = new adapter.GraphicsContext();
            let fb  = new adapter.Framebuffer(ctx);
            //assert.notEqual(fb.getGlName(), 0);
        });

        it('constructs unique gl names', function() {
            let ctx = new adapter.GraphicsContext();
            let fb1 = new adapter.Framebuffer(ctx);
            let fb2 = new adapter.Framebuffer(ctx);

            //assert.notEqual(fb1.getGlName(), 0);
            //assert.notEqual(fb2.getGlName(), 0);
            //assert.notEqual(fb1.getGlName(), fb2.getGlName());
        });

        it('attaches rgba texture', function() {
            let ctx = new adapter.GraphicsContext();
            let fb  = new adapter.Framebuffer(ctx);
            ctx.check('during test');

            let texture = ctx.texture(ctx, 64, 64, 'rgba');
            fb.attach(texture);

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
