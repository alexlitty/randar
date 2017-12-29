describe('Skeleton', function() {
    it('clears joints', function() {
        let skeleton = randar.skeleton();
        assert.equal(skeleton.jointCount(), 0);

        skeleton.add('thing');
        skeleton.add('a');
        skeleton.add('roo');
        assert.equal(skeleton.jointCount(), 3);

        skeleton.clear();
        assert.equal(skeleton.jointCount(), 0);
    });

    it('resets joints to identity', function() {
        let skeleton = randar.skeleton();
        let joint = skeleton.add('thing');
        joint.move(randar.vector(5, 6, 7));

        assert.equal(joint.position().x, 5);
        assert.equal(joint.position().y, 6);
        assert.equal(joint.position().z, 7);

        skeleton.reset();
        assert.equal(joint.position().x, 0);
        assert.equal(joint.position().y, 0);
        assert.equal(joint.position().z, 0);
    });

    it('resets joints to state', function() {
        let skeleton = randar.skeleton();
        skeleton.add('neck').move(randar.vector(1, 2, 3));
        skeleton.add('tie').move(randar.vector(4, 5, 6));

        assert.equal(skeleton.joint('neck').position().x, 1);
        assert.equal(skeleton.joint('neck').position().y, 2);
        assert.equal(skeleton.joint('neck').position().z, 3);

        assert.equal(skeleton.joint('tie').position().x, 4);
        assert.equal(skeleton.joint('tie').position().y, 5);
        assert.equal(skeleton.joint('tie').position().z, 6);

        let state = randar.skeleton.state();
        state.joint('neck').move(randar.vector(10, 20, 30));
        skeleton.reset(state);

        assert.equal(skeleton.joint('neck').position().x, 10);
        assert.equal(skeleton.joint('neck').position().y, 20);
        assert.equal(skeleton.joint('neck').position().z, 30);

        assert.equal(skeleton.joint('tie').position().x, 0);
        assert.equal(skeleton.joint('tie').position().y, 0);
        assert.equal(skeleton.joint('tie').position().z, 0);
    });

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

        let win = new randar.Window(800, 600);
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

    it('applies states', function() {
        let skel = randar.skeleton();
        let state = randar.skeleton.state();
        state.joint('foo').move(randar.vector(2, 3, 4));

        skel.apply(state);
        assert.equal(skel.jointCount(), 0);

        skel.add('foo');
        skel.add('bar');
        for (let name of ['foo', 'bar']) {
            assert.equal(skel.joint(name).position().x, 0);
            assert.equal(skel.joint(name).position().y, 0);
            assert.equal(skel.joint(name).position().z, 0);
        }

        skel.joint('bar').move(randar.vector(1, 1, 1));

        skel.apply(state);
        assert.equal(skel.joint('foo').position().x, 2);
        assert.equal(skel.joint('foo').position().y, 3);
        assert.equal(skel.joint('foo').position().z, 4);
        assert.equal(skel.joint('bar').position().x, 1);
        assert.equal(skel.joint('bar').position().y, 1);
        assert.equal(skel.joint('bar').position().z, 1);
    });

    it('extracts states', function() {
        let skel = randar.skeleton();
        skel.add('foot').move(randar.vector(1, 2, 3));
        skel.add('mouth').move(randar.vector(4, 5, 6));

        let state = skel.state();
        assert.equal(state.has('foot'), true);
        assert.equal(state.has('mouth'), true);

        assert.equal(state.joint('foot').position().x, 1);
        assert.equal(state.joint('foot').position().y, 2);
        assert.equal(state.joint('foot').position().z, 3);

        assert.equal(state.joint('mouth').position().x, 4);
        assert.equal(state.joint('mouth').position().y, 5);
        assert.equal(state.joint('mouth').position().z, 6);
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
