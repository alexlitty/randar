global.randar = require('../');

global.ctx    = new randar.GraphicsContext();
global.win    = ctx.window(800, 600);
global.camera = win.camera();

camera.projection();
camera.position(randar.vector(10, 10, 10));
camera.target(randar.vector(0, 0, 0));

function generateBlade(model, width, height, depth) {
    let layers = 24;
    let layerHeight = height / layers;

    let geo = model.geometry();
    for (let i = 0; i < layers; i++) {
        let vertex = randar.vertex().withJoint(0, 255)//.withJoint(0, (i / layers) * 255);
        let h = layerHeight * i;

        let opt = { };

        opt.frontBottomLeft  = vertex.withPosition(0, h, 0);
        opt.frontBottomRight = vertex.withPosition(width, h, 0);
        opt.backBottomLeft   = vertex.withPosition(0, h, depth);
        opt.backBottomRight  = vertex.withPosition(width, h, depth);

        vertex = vertex.withJoint(0, 255)//.withJoint(0, ((i + 1) / layers) * 255);
        h = layerHeight * (i + 1);

        opt.frontTopLeft     = vertex.withPosition(0, h, 0);
        opt.frontTopRight    = vertex.withPosition(width, h, 0);
        opt.backTopLeft      = vertex.withPosition(0, h, depth);
        opt.backTopRight     = vertex.withPosition(width, h, depth);

        geo.append(randar.generate.cuboid(opt));
    }

    model.skeleton().add('tip');
    return model;
}

let geometries = [];
let skeletons  = [];
let models     = [];

for (let i = 0; i < 1; i++) {
    models.push(randar.model());
    geometries.push(randar.geometry());
    skeletons.push(randar.skeleton());

    models[i].geo = geometries[i];
    models[i].skel = skeletons[i];

    generateBlade(models[i], 1, 24, 1);
}

setInterval(() => {
    camera.move(
        randar.vector(0, 1, 0),
        randar.angle(0.01)
    );

    win.clear();
    for (let i = 0; i < models.length; i++) {
        win.draw(models[i]);
    }
    win.present();
}, 0);
