describe.only('Lights', function() {
    let ctx;
    let win;
    let camera;
    let world;

    let geometryWall;
    let modelWall;

    let geometryBall;
    let modelBall;

    before(function() {
        ctx = new randar.GraphicsContext();
        win = ctx.window(800, 600);

        camera = win.camera();
        camera.projection();
        camera.position(randar.vector(0, 20, 30));
        camera.target(randar.vector(0, 0, -20));
        camera.range(-10, 50);
        geometryWall = randar.generate.square(100);
        modelWall = randar.model();
        modelWall.geometry(geometryWall);
        modelWall.move(randar.vector(0, 0, -50));

        geometryBall = randar.generate.cuboid(200, 5, 1);
        modelBall = randar.model();
        modelBall.geometry(geometryBall);
        modelBall.move(randar.vector(0, 0, 5));

        world = randar.world();
        world.models.add(modelWall);
        world.models.add(modelBall);
    });

    it('Spotlight', function() {
        this.timeout(8000);
        let light = ctx.spotlight();
        world.lights.add(light);

        light.generateMap(world);
        light.map().image().save("/tmp/test.png");

        win.fps(24);
        for (let i = 0; i < 72; i++) {
            camera.move(randar.vector(-1, 3, -3));
            win.draw(world);
            win.present();
        }
    });
});
