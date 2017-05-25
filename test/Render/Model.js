describe('Model', function() {
    let ctx;
    let win;
    let fb;

    before(function() {
        ctx = new randar.GraphicsContext();
        win = ctx.window(400, 400);
        fb  = win.framebuffer();

        fb.camera.projection();
        fb.fps = 24;
    });

    beforeEach(function() {
        fb.camera.position(randar.vector(0, 0, 1));
        fb.camera.target(randar.vector(0, 0, 0));
    });

    after(function() {
        win.close();
    });

    it('draws with transformations', function() {
        this.timeout(10000);

        let model = randar.model();
        let geo   = randar.sphere(1);
        model.geometry(geo);

        for (let i = 0; i < 120; i++) {
            model.move(randar.vector(0.02, 0.01, -0.05));

            fb.clear(randar.color(0.3, 0.3, 0));
            fb.draw(model);
            win.present();
        }
    });
});
