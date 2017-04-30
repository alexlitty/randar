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

describe('Framebuffer', function() {
    describe('window', function() {
        let ctx;
        
        beforeEach(function() {
            ctx = new adapter.GraphicsContext();
        });

        afterEach(function() {
            ctx = null;
        });

        it('constructs with window', function() {
            let win = ctx.window(600, 480);
            let fb  = win.framebuffer();
            assert.equal(fb.getGlName(), 0);
        });

        it('assigned by reference', function() {
            let win = ctx.window(64, 64);

            const color1 = new adapter.Color(
                0.6705882549285889,
                0.34117648005485535,
                0.9098039269447327,
                0.21960784494876862
            );

            const color2 = new adapter.Color(
                0.250980406999588,
                0.7490196228027344,
                0.2980392277240753,
                0.8705882430076599
            );

            let fb1 = win.framebuffer();
            fb1.clear(color1);
            win.present();

            fb1.clear(color1);
            assertCleared(fb1, color1);

            let fb2 = fb1;
            fb2.clear(color2);
            assertCleared(fb2, color2);
            assertCleared(fb1, color2);
        });

        it('refuses attachments', function() {
            let win = ctx.window(800, 600);
            let fb  = win.framebuffer();

            let texture = ctx.texture(800, 600, 'rgba');
            assert.throws(() => fb.attach(texture));
        });

        it('clears with black by default', function() {
            let win = ctx.window(200, 200);
            let fb  = win.framebuffer();

            fb.clear();
            win.present();

            fb.clear();
            assertCleared(fb, new adapter.Color(0, 0, 0, 1));
        });

        it('clears specific color', function() {
            let win = ctx.window(300, 100);
            let fb  = win.framebuffer();
            const color = new adapter.Color(
                0.250980406999588,
                0.7490196228027344,
                0.2980392277240753
            );

            fb.clear(color);
            assertCleared(fb, color);

            win.present();
            fb.clear(color);
            assertCleared(fb, color);
        });
    });

    describe('off-screen', function() {
        it('constructs with context', function() {
            let ctx = new adapter.GraphicsContext();
            let fb  = ctx.framebuffer();
            assert.notEqual(fb.getGlName(), 0);
        });

        it('constructs unique gl names', function() {
            let ctx = new adapter.GraphicsContext();
            let fb1 = ctx.framebuffer();
            let fb2 = ctx.framebuffer();

            assert.notEqual(fb1.getGlName(), 0);
            assert.notEqual(fb2.getGlName(), 0);
            assert.notEqual(fb1.getGlName(), fb2.getGlName());
        });

        it('attaches rgba texture', function() {
            let ctx = new adapter.GraphicsContext();
            let fb  = ctx.framebuffer();
            ctx.check('during test');

            let texture = ctx.texture(64, 64, 'rgba');
            fb.attach(texture);

            assert.notEqual(fb.getGlName(), 0);
            assert.equal(fb.getWidth(), texture.getWidth());
            assert.equal(fb.getHeight(), texture.getHeight());
        });
    });
});
