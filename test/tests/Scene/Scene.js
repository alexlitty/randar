const _ = require('underscore');

describe('Scene', function() {
    it('constructs an empty scene', function() {
        let scene = randar.scene();

        assert.equal(scene.calculateFrameCount(), 1);
        assert.equal(scene.actions.length, 0);
        assert.equal(_.size(scene.modelItems), 0);
        assert.equal(scene.frameStates, 0);
    });

    describe('compilation', function() {
        it('compiles an empty scene', function() {
            let scene = randar.scene();
            scene.compile();

            assert.equal(scene.frameStates.length, 1);
            assert.equal(_.size(scene.frameStates[0].modelItems), 0);
        });

        it('compiles with models & no actions', function() {
            let scene = randar.scene();
            scene.modelItems[42] = { id: 42 };
            scene.modelItems[56] = { id: 56 };

            scene.compile();
            assert.equal(scene.frameStates.length, 1);
            assert.equal(_.size(scene.frameStates[0].modelItems), 2);
        });
    });

    describe('transformations', function() {
        let scene;
        beforeEach(function() {
            scene = randar.scene();
            scene.modelItems[0] = { id: 0 };
        });

        it('rejects invalid translations', function() {
            scene.actions = [{ kind: 'translation' }];
            assert.throws(() => scene.compile());

            scene.actions = [{ kind: 'translation', translation: new Date() }];
            assert.throws(() => scene.compile());

            scene.actions = [{
                kind        : 'translation',
                modelItemId : 0,
                translation : {
                    x : 1,
                    y : 2,
                    z : new Date()
                }
            }];
            assert.throws(() => scene.compile());
        });

        it('transforms in a single frame', function() {
            let scene = randar.scene();
            scene.modelItems[0] = { id: 0 };

            scene.actions.push({
                kind        : 'transform',
                modelItemId : 0,
                frame       : 0,
                frameCount  : 1,
                translation : {
                    x : 1,
                    y : 2,
                    z : -5
                }
            });

            scene.actions.push({
                kind        : 'transform',
                modelItemId : 0,
                frame       : 2,
                frameCount  : 1,
                translation : {
                    x : -16,
                    y : 6,
                    z : 49
                }
            });

            scene.compile();
            assert.equal(scene.frameStates.length, 3);

            for (let i = 0; i < 2; i++) {
                let transform = scene.frameStates[i].modelItems[0].transform;
                assert.equal(transform.position.x, 1);
                assert.equal(transform.position.y, 2);
                assert.equal(transform.position.z, -5);
            }

            let transform = scene.frameStates[2].modelItems[0].transform;
            assert.equal(transform.position.x, -15);
            assert.equal(transform.position.y, 8);
            assert.equal(transform.position.z, 44);
        });

        it('transforms over multiple frames', function() {
            scene.actions.push({
                kind        : 'transform',
                modelItemId : 0,
                frame       : 0,
                frameCount  : 3,
                translation : {
                    x : 9,
                    y : -27,
                    z : 3
                }
            });

            scene.compile();
            assert.equal(scene.frameStates.length, 3);

            let transform = scene.frameStates[0].modelItems[0].transform;
            assert.equal(transform.position.x, 3);
            assert.equal(transform.position.y, -9);
            assert.equal(transform.position.z, 1);

            transform = scene.frameStates[1].modelItems[0].transform;
            assert.equal(transform.position.x, 6);
            assert.equal(transform.position.y, -18);
            assert.equal(transform.position.z, 2);

            transform = scene.frameStates[2].modelItems[0].transform;
            assert.equal(transform.position.x, 9);
            assert.equal(transform.position.y, -27);
            assert.equal(transform.position.z, 3);
        });
    });

    it('draw frames to a canvas', function() {
        this.timeout(30000);

        let ctx    = new randar.GraphicsContext();
        let win    = ctx.window(800, 600);
        let camera = win.camera();

        win.fps(24);
        camera.projection();
        camera.position(randar.vector(0, 0, -5));
        camera.target(randar.vector(0, 0, 0));

        let project = randar.project(path.join(__dirname, '..', '..', 'fixtures', 'project'));
        let scene   = randar.scene();

        scene.modelItems[0] = project.items[0];
        scene.actions.push({
            kind        : 'transform',
            modelItemId : 0,
            frame       : 0,
            frameCount  : 48,
            translation : {
                x : 5,
                y : 3,
                z : 10
            }
        });

        scene.compile();
        assert.equal(scene.frameStates.length, 48);

        for (let i = 0; i < scene.frameStates.length; i++) {
            scene.drawFrame(win, i);
            win.present();
        }

        win.close();
    });
});