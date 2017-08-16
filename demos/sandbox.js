global.randar = require('../');

global.ctx    = new randar.GraphicsContext();
global.win    = ctx.window(800, 600);
global.camera = win.camera();
global.world  = randar.world();

camera.projection();
camera.position(randar.vector(10, 10, 10));
camera.target(randar.vector(0, 0, 0));

setInterval(() => {
    camera.move(
        randar.vector(0, 1, 0),
        randar.angle(0.01)
    );

    win.draw(world);
    win.present();
}, 0);
