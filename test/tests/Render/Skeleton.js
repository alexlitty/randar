describe('Skeleton', function() {
    it('retains correct joint data', function() {
        let skeleton = randar.skeleton();

        skeleton.add('chest');
        skeleton.add('neck', 'chest');
        skeleton.add('head', 'neck');
        skeleton.add('leftEar', 'head');
        skeleton.add('rightEar', 'head');

        assert.equal(skeleton.jointCount(), 5);
        assert.equal(skeleton.jointName(0), 'chest');
        assert.equal(skeleton.jointName(1), 'neck');
        assert.equal(skeleton.jointName(2), 'head');
        assert.equal(skeleton.jointName(3), 'leftEar');
        assert.equal(skeleton.jointName(4), 'rightEar');
    });

    it('retrieves joints', function() {
        let skeleton = randar.skeleton();
        skeleton.add('foot');
        skeleton.add('toe', 'foot');

        skeleton.joint('foot');
        skeleton.joint('toe');

        skeleton.joint(0);
        skeleton.joint(1);
    });

    it('rejects bad joint retrievals', function() {
        let skeleton = randar.skeleton();
        skeleton.add('stump');

        assert.throws(() => skeleton.joint('frump'));
        assert.throws(() => skeleton.joint(1));
        assert.throws(() => skeleton.jointName(2));
        assert.throws(() => skeleton.jointIndex('wump'));
    });

    it.only('applies skeletons to geometry', function() {
        this.timeout(6000);

        let ctx = new randar.GraphicsContext();
        let win = ctx.window(800, 600);
        win.fps(24);

        let camera = win.camera();
        camera.projection();
        camera.move(randar.vector(10, 10, 10));
        camera.target(randar.vector(0, 0, 0));

        let geo = randar.generate.cube({
            width : 5,
            joint : 0
        });

        let skeleton = randar.skeleton();
        skeleton.add("root");

        let joint = skeleton.joint("root");

        let drawState = randar.drawState({
            skeleton : skeleton
        });

        for (let i = 0; i < 24; i++) {
            joint.move(randar.vector(0, -0.5, -0.5));
            win.clear();
            win.draw(geo, drawState);
            win.present();
        }

        win.close();
    });
});
