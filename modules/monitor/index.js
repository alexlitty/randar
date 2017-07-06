const args  = require('minimist')(process.argv.slice(2));
const watch = require('watch');

const randar = require('../wrapper');

if (!args.project || !args.project.length) {
    console.error('Specify a project with: --project "/directory/to/project"');
    process.exit(1);
}

if (typeof args.item === 'undefined') {
    console.error('Specify a project item with: --item #');
    process.exit(1);
}

global.project = randar.project();
if (!project.load(args.project)) {
    process.exit(1);
}

global.item = project.items[args.item];
if (!item) {
    console.error('Item does not exist');
    process.exit(1);
}

global.ctx = new randar.GraphicsContext();
global.monitor = ctx.monitor(item.object());

process.on('message', (data) => {
    if (data.cmd === 'reload') {
        console.log('reloading');
        item.load();
    }

    else {
        console.error('Ignoring unknown command:', data.cmd);
    }
});

function present() {
    if (monitor.window().isOpen()) {
        monitor.present();
        setTimeout(present, 0);
    }
}

monitor.window().fps(24);
present();
