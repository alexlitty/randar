describe('Shape', function() {
    this.timeout(4000);

    let ctx;
    let win;
    let camera;
    let cameraQuat;

    function moveCamera() {
        win.camera().position(cameraQuat.transform(win.camera().position()));
    }

    before(function() {
        ctx = new randar.GraphicsContext();
        win = ctx.window(800, 600);

        camera = win.camera();
        camera.projection();

        cameraQuat = randar.quaternion(
            randar.vector(0, 1, 0),
            randar.angle(0.025)
        );
    });

    beforeEach(function() {
        camera.position(randar.vector(300, 300, 100));
        camera.target(randar.vector(0, 0, 0));
    });

    after(function() {
        win.close();
    });

    it('generates circles', function() {
        this.timeout(10000);

        for (let k = 3; k < 30; k += 5) {
            for (let i = 0; i < 60; i++) {
                let geo = randar.generate.circle(i, k);

                moveCamera();
                win.clear();
                win.draw(geo);
                win.present();
            }
        }
    });

    it('generates cones', function() {
        this.timeout(10000);

        for (let k = 3; k < 30; k+= 5) {
            for (let i = 0; i < 60; i++) {
                let geo = randar.generate.cone(i, 90, k);

                moveCamera();
                win.clear();
                win.draw(geo);
                win.present();
            }
        }
    });

    it('generates cubes', function() {
        this.timeout(10000);

        for (let i = 0; i < 180; i++) {
            let geo = randar.generate.cube(i);

            moveCamera();
            win.clear();
            win.draw(geo);
            win.present();
        }
    });

    it('generates cuboids', function() {
        this.timeout(10000);

        for (let i = 0; i < 180; i++) {
            let geo = randar.generate.cuboid(i, i * 0.75, i * 0.5);

            moveCamera();
            win.clear();
            win.draw(geo);
            win.present();
        }
    });

    it('generates cylinders', function() {
        this.timeout(10000);

        for (let k = 3; k <= 48; k *= 2) {
            for (let i = 0; i < 90; i++) {
                let geo = randar.generate.cylinder(i, 60, k);

                moveCamera();
                win.clear();
                win.draw(geo);
                win.present();
            }
        }
    });

    it('generates rectangles', function() {
        this.timeout(10000);

        for (let i = 0; i < 90; i++) {
            let geo = randar.generate.rectangle(i, i * 0.75);

            moveCamera();
            win.clear();
            win.draw(geo);
            win.present();
        }
    });

    it('generates spheres', function() {
        this.timeout(10000);

        for (let i = 0; i < 60; i++) {
            let geo = randar.generate.sphere(i, 24, 24);

            moveCamera();
            win.clear();
            win.draw(geo);
            win.present();
        }
    });

    it('generates squares', function() {
        this.timeout(10000);

        for (let i = 0; i < 90; i++) {
            let geo = randar.generate.square(i);

            moveCamera();
            win.clear();
            win.draw(geo);
            win.present();
        }
    });
});
