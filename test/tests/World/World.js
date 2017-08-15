describe('world', function() {
    let ctx;
    let win;
    let world;
    let camera;

    before(function() {
        ctx = new randar.GraphicsContext();
        win = ctx.window(800, 600);
        win.fps(24);

        camera = win.camera();
        camera.position(randar.vector(0, 0, 5));
        camera.target(randar.vector(0, 0, 0));
        camera.projection();
    });

    beforeEach(function() {
        world = randar.world();
    });

    it('draws while empty', function() {
        win.draw(world);
        win.present();
    });

    it('draws correct background color', function() {
        world.backgroundColor = randar.color(0.5, 0.1, 0.2);
        win.draw(world);
        let image = win.image();
        let pixel = image.getPixel(0, 0);

        assert.equal(pixel.r().toFixed(1), 0.5);
        assert.equal(pixel.g().toFixed(1), 0.1);
        assert.equal(pixel.b().toFixed(1), 0.2);
        assert.equal(pixel.a().toFixed(1), 1.0);
    });

    it.only('draws with models', function() {
        this.timeout(10000);
        let model = randar.model();
        let geo   = randar.generate.sphere({
            radius           : 0.5,
            verticalPoints   : 8,
            horizontalPoints : 8
        });

        model.geometry(geo);
        world.models.add(model);

        for (let i = 0; i < 48; i++) {
            model.rotationAxis(randar.vector(0, 1, 0));
            model.rotate(randar.angle(400));
            model.move(randar.vector(0, 0, -0.05));
            win.draw(world);
            win.present();
        }
    });
});
