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
        assert.equal(skeleton.hasJoint('chest'), true);

        assert.equal(skeleton.jointName(1), 'neck');
        assert.equal(skeleton.hasJoint('neck'), true);

        assert.equal(skeleton.jointName(2), 'head');
        assert.equal(skeleton.hasJoint('head'), true);

        assert.equal(skeleton.jointName(3), 'leftEar');
        assert.equal(skeleton.hasJoint('leftEar'), true);

        assert.equal(skeleton.jointName(4), 'rightEar');
        assert.equal(skeleton.hasJoint('rightEar'), true);

        assert.equal(skeleton.hasJoint('middleEar'), false);
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

    it('applies skeletons to geometry', function() {
        this.timeout(6000);

        let ctx = new randar.GraphicsContext();
        let win = ctx.window(800, 600);
        win.fps(24);

        let camera = win.camera();
        camera.projection();
        camera.move(randar.vector(10, 10, 20));
        camera.target(randar.vector(0, 5, 0));

        let geo = randar.generate.cube({
            width : 1,
            joint : 0
        });

        let skeleton = randar.skeleton();
        skeleton.add('0');

        for (let i = 0; i < 10; i++) {
            let transform = randar.transform();
            transform.move(randar.vector(0, i + 1, 0));

            geo.append(randar.generate.cube({
                width : 1,
                joint : i + 1
            }), transform);

            skeleton.add((i + 1).toString(), i.toString());
        }

        let drawState = randar.drawState({
            skeleton : skeleton
        });

        for (let i = 0; i < 72; i++) {
            for (let j = 0; j < 11; j++) {
                let joint = skeleton.joint(j.toString());
                let factor = 0.01 * Math.cos(6 * (i / 48));
                joint.move(randar.vector(factor * j, 0, 0));
            }

            win.clear();
            win.draw(geo, drawState);
            win.present();
        }

        win.close();
    });

    describe('State', function() {
        it('creates joints', function() {
            let state = randar.skeleton.state();
            assert.equal(state.has('foo'), false);
            state.joint('foo');
            assert.equal(state.has('foo'), true);
        });

        it('removes joints', function() {
            let state = randar.skeleton.state();
            state.joint('bar');
            assert.equal(state.has('bar'), true);
            state.remove('bar');
            assert.equal(state.has('bar'), false);
        });
    });
});
