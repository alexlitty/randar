global.randar = require('../');

global.ctx    = new randar.GraphicsContext();
global.win    = ctx.window(800, 600);
global.camera = win.camera();
global.world  = randar.world();

camera.projection();
camera.position(randar.vector(10, 10, 20));
camera.target(randar.vector(0, 0, 0));

// Build skeleton.
global.skeleton = randar.skeleton();
let skeletonJoints = [
    { name: 'root' },

    { name: 'chest.mid', parent: 'root' },
    { name: 'chest.upper', parent: 'chest.mid' },
    { name: 'chest.lower', parent: 'chest.mid' },

    { name: 'head', parent: 'chest.upper' },

    { name: 'arm.upper.left', parent: 'chest.upper' },
    { name: 'arm.lower.left', parent: 'arm.upper.left' },
    { name: 'hand.left', parent: 'arm.lower.left' },
    { name: 'finger.thumb.left', parent: 'hand.left' },
    { name: 'finger.index.left', parent: 'hand.left' },
    { name: 'finger.middle.left', parent: 'hand.left' },
    { name: 'finger.ring.left', parent: 'hand.left' },
    { name: 'finger.pinky.left', parent: 'hand.left' },

    { name: 'arm.upper.right', parent: 'chest.upper' },
    { name: 'arm.lower.right', parent: 'arm.upper.right' },
    { name: 'hand.right', parent: 'arm.lower.right' },
    { name: 'finger.thumb.right', parent: 'hand.right' },
    { name: 'finger.index.right', parent: 'hand.right' },
    { name: 'finger.middle.right', parent: 'hand.right' },
    { name: 'finger.ring.right', parent: 'hand.right' },
    { name: 'finger.pinky.right', parent: 'hand.right' },

    { name: 'leg.upper.left', parent: 'chest.lower' },
    { name: 'leg.lower.left', parent: 'leg.upper.left' },
    { name: 'foot.left', parent: 'leg.lower.left' },

    { name: 'leg.upper.right', parent: 'chest.lower' },
    { name: 'leg.lower.right', parent: 'leg.upper.right' },
    { name: 'foot.right', parent: 'leg.lower.right' }
];

for (joint of skeletonJoints) {
    if (joint.parent) {
        skeleton.add(joint.name, joint.parent);
    } else {
        skeleton.add(joint.name);
    }
}

// Build geometry.
let cuboidParts = [
    { joint: 'chest.mid', x: 0, y: 0, z: 0, width: 5, height: 2, depth: 1 },
    { joint: 'chest.upper', x: 0, y: 2.5, z: 0, width: 6, height: 2, depth: 1 },
    { joint: 'chest.lower', x: 0, y: -2.5, z: 0, width: 4, height: 2, depth: 1 },

    { joint: 'head', x: 0, y: 6, z: 0, width: 4, height: 4, depth: 1 },

    { joint: 'arm.upper.left', x: -5.5, y: 2.5, z: 0, width: 4, height: 1.5, depth: 1 },
    { joint: 'arm.lower.left', x: -10, y: 2.5, z: 0, width: 4, height: 1.5, depth: 1 },
    { joint: 'hand.left', x: -13.5, y: 2.5, z: 0, width: 2, height: 2, depth: 1 },

    { joint: 'arm.upper.right', x: 5.5, y: 2.5, z: 0, width: 4, height: 1.5, depth: 1 },
    { joint: 'arm.lower.right', x: 10, y: 2.5, z: 0, width: 4, height: 1.5, depth: 1 },
    { joint: 'hand.right', x: 13.5, y: 2.5, z: 0, width: 2, height: 2, depth: 1 },

    { joint: 'leg.upper.left', x: -1.25, y: -6.5, z: 0, width: 1.5, height: 5, depth: 1 },
    { joint: 'leg.lower.left', x: -1.25, y: -12, z: 0, width: 1.5, height: 5, depth: 1 },
    { joint: 'foot.left', x: -1.25, y: -15.5, z: 0.5, width: 1.5, height: 1, depth: 2 },

    { joint: 'leg.upper.right', x: 1.25, y: -6.5, z: 0, width: 1.5, height: 5, depth: 1 },
    { joint: 'leg.lower.right', x: 1.25, y: -12, z: 0, width: 1.5, height: 5, depth: 1 },
    { joint: 'foot.right', x: 1.25, y: -15.5, z: 0.5, width: 1.5, height: 1, depth: 2 },
];

global.geo = randar.geometry();
for (part of cuboidParts) {
    let transform = randar.transform();
    transform.position(randar.position(part.x, part.y, part.z));

    geo.append(randar.generate.cuboid({
        width  : part.width,
        height : part.height,
        depth  : part.depth,
        joint  : skeleton.jointIndex(part.joint)
    }), transform);
}

global.model = randar.model();
model.skel = skeleton;
model.geo = geo;

world.models.add(model);

setInterval(() => {
    camera.move(
        randar.vector(0, 1, 0),
        randar.angle(0.01)
    );

    //let joint = skeleton.joint('chest.upper');
    //joint.rotate(randar.angle(0.05));
    //console.log(randar.toString(joint.transformMatrix()));

    /*let transform = randar.transform();
    transform.rotation(randar.position(Math.random(), Math.random(), Math.random()), randar.angle(1.5 + Math.random()));
    console.log(randar.toString(transform.transformMatrix()));*/

    win.draw(world);
    win.present();
}, 0);
