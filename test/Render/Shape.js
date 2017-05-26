describe('Shape', function() {
    this.timeout(4000);

    let ctx;
    let win;
    let fb;

    before(function() {
        ctx = new randar.GraphicsContext();
        win = ctx.window(200, 200);
        fb  = win.framebuffer();
    });

    after(function() {
        win.close();
    });

    describe('sphere', function() {
        it('draws to window', function() {
            this.timeout(10000);

            for (let i = 0; i < 60; i++) {
                let geo = randar.sphere(i / 60);

                fb.clear(randar.color(0.3, 0, 0.3));
                fb.draw(geo);
                win.present();
            }
        });
    });
});
