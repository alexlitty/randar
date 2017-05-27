function assertColor(color, expectedColor, msg) {
    assert.equal(color.r().toFixed(3), expectedColor.r().toFixed(3), msg); 
    assert.equal(color.g().toFixed(3), expectedColor.g().toFixed(3), msg);
    assert.equal(color.b().toFixed(3), expectedColor.b().toFixed(3), msg);
    assert.equal(color.a().toFixed(3), expectedColor.a().toFixed(3), msg);
}

function assertCleared(readable, expectedColor) {
    let image = readable.image();

    assert(image.hasDimensions());
    assert.equal(image.getWidth(), readable.getWidth());
    assert.equal(image.getHeight(), readable.getHeight());
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
            ctx = new randar.GraphicsContext();
        });

        afterEach(function() {
            ctx = null;
        });

        it('constructs with window', function() {
            let win = ctx.window(600, 480);
            let fb  = win.framebuffer();
            assert.equal(fb.getGlName(), 0);
            win.close();
        });

        it('assigned by reference', function() {
            let win = ctx.window(64, 64);

            const color1 = new randar.Color(
                0.6705882549285889,
                0.34117648005485535,
                0.9098039269447327,
                0.21960784494876862
            );

            const color2 = new randar.Color(
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

            win.close();
        });

        it('refuses attachments', function() {
            let win = ctx.window(800, 600);
            let fb  = win.framebuffer();

            let texture = ctx.texture(800, 600, 'rgba');
            assert.throws(() => fb.attach(texture));

            win.close();
        });

        it('clears with purple by default', function() {
            let win = ctx.window(200, 200);
            let fb  = win.framebuffer();

            fb.clear();
            win.present();

            fb.clear();
            assertCleared(fb, new randar.Color(0.29, 0.00, 0.29, 1));

            win.close();
        });

        it('clears specific color', function() {
            let win = ctx.window(300, 100);
            let fb  = win.framebuffer();
            const color = new randar.Color(
                0.250980406999588,
                0.7490196228027344,
                0.2980392277240753
            );

            fb.clear(color);
            assertCleared(fb, color);

            win.present();
            fb.clear(color);
            assertCleared(fb, color);

            win.close();
        });
    });

    describe('off-screen', function() {
        it('constructs with context', function() {
            let ctx = new randar.GraphicsContext();
            let fb  = ctx.framebuffer();
            assert.notEqual(fb.getGlName(), 0);
        });

        it('constructs unique gl names', function() {
            let ctx = new randar.GraphicsContext();
            let fb1 = ctx.framebuffer();
            let fb2 = ctx.framebuffer();

            assert.notEqual(fb1.getGlName(), 0);
            assert.notEqual(fb2.getGlName(), 0);
            assert.notEqual(fb1.getGlName(), fb2.getGlName());
        });

        it('attaches rgba texture', function() {
            let ctx = new randar.GraphicsContext();
            let fb  = ctx.framebuffer();

            let texture = ctx.texture(64, 64, 'rgba');
            fb.attach(texture);

            assert.notEqual(fb.getGlName(), 0);
            assert.equal(fb.getWidth(), 64);
            assert.equal(fb.getHeight(), 64);
        });

        it('writes to rgba texture', function() {
            let ctx   = new randar.GraphicsContext();
            let fb    = ctx.framebuffer();
            let color = new randar.Color(
                0.250980406999588,
                0.7490196228027344,
                0.2980392277240753,
                0.8705882430076599
            );

            let texture = ctx.texture(128, 128, 'rgba');
            fb.attach(texture);

            fb.clear(color);
            assertCleared(fb, color);
            assertCleared(texture, color);
        });
    });
});
