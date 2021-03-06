describe('Model', function() {
    let win;
    let camera;

    before(function() {
        win    = new randar.Window(400, 400);
        camera = win.camera();

        win.fps(24);
        camera.projection();
    });

    beforeEach(function() {
        camera.position(randar.vector(0, 0, 1));
        camera.target(randar.vector(0, 0, 0));
    });

    after(function() {
        win.close();
    });

    it('draws with transformations', function() {
        this.timeout(10000);

        let model = randar.model();
        let geo   = randar.generate.sphere({
            radius           : 1,
            verticalPoints   : 3,
            horizontalPoints : 3
        });

        model.geometry(geo);

        for (let i = 0; i < 30; i++) {
            model.move(randar.vector(0.02, 0.01, -0.05));

            win.clear(randar.color(0.3, 0.3, 0));
            win.draw(model);
            win.present();
        }
    });
});
