describe('Lights', function() {
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
        camera.position(randar.vector(-500, 500, -1000));
        camera.target(randar.vector(0, 0, 0));
        camera.range(0.1, 10000);

        geometryWall = randar.generate.cuboid({
            width  : 300,
            height : 300,
            depth  : 300
        });

        geometryBall = randar.generate.sphere({
            radius           : 300,
            verticalPoints   : 20,
            horizontalPoints : 20
        });

        modelWall = randar.model();
        modelWall.geometry(geometryWall);
        modelWall.move(randar.vector(0, 0, 0));

        modelBall = randar.model();
        modelBall.geometry(geometryBall);
        modelBall.move(randar.vector(-46, -500, 500));

        world = randar.world();
        world.models.add(modelWall);
        world.models.add(modelBall);
    });

    after(function() {
        win.close();
    });

    it('Spotlight', function() {
        this.timeout(8000);
        let light = ctx.spotlight();
        world.lights.add(light);

        light.range(0.01, 10000);
        light.position(randar.vector(0, -400, 2000));
        //light.target(randar.vector(-46, -500, 500));
        light.target(randar.vector(0, 0, 0));

        win.fps(24);
        for (let i = 0; i < 72; i++) {
            camera.move(randar.vector(0, 0, 20));
            light.move(randar.vector(0, -100, 0));

            win.draw(world);
            win.present();
        }
    });
});
