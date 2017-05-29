describe('Shape', function() {
    this.timeout(4000);

    let ctx;
    let win;
    let camera;

    before(function() {
        ctx = new randar.GraphicsContext();
        win = ctx.window(800, 600);

        camera = win.camera();
        camera.projection();
    });

    beforeEach(function() {
        camera.position(randar.vector(300, 300, 100));
        camera.target(randar.vector(0, 0, 0));
    });

    after(function() {
        win.close();
    });

    it('generates spheres', function() {
        this.timeout(10000);

        for (let i = 0; i < 60; i++) {
            let geo = randar.sphere(i);

            win.clear();
            win.draw(geo);
            win.present();
        }
    });

    it('generates cuboids', function() {
        this.timeout(10000);

        for (let i = 0; i < 180; i++) {
            let geo = randar.cuboid(i, i * 0.75, i * 0.5);

            win.clear();
            win.draw(geo);
            win.present();
        }
    });
});
