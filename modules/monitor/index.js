const args   = require('minimist')(process.argv.slice(2));
const randar = require('../wrapper');

if (!args.project || !args.project.length) {
    console.error('Specify a project with: --project "/directory/to/project"');
    process.exit(1);
}

if (typeof args.item === 'undefined') {
    console.error('Specify a project item with: --item #');
    process.exit(1);
}

let project = randar.project();
if (!project.load(args.project)) {
    process.exit(1);
}

let item = project.items[args.item];
if (!item) {
    console.error('Item does not exist');
    process.exit(1);
}

let ctx = new randar.GraphicsContext();
let monitor = ctx.monitor(item.object());

monitor.window().fps(24);
while (monitor.window().isOpen()) {
    monitor.present();
}