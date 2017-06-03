const {app, BrowserWindow} = require('electron');

const fs   = require('fs');
const path = require('path');
const url  = require('url');

const args = process.argv;
if (args.length < 3) {
    console.error('No view provided');
    process.exit(1);
}

const filepath = path.join(__dirname, 'build', `${args[2]}.html`);
if (!fs.existsSync(filepath)) {
    console.error('Nonexistent view');
    process.exit(1);
}

let win;
app.on('ready', () => {
    win = new BrowserWindow({
        minWidth  : 600,
        minHeight : 480,

        width  : 600,
        height : 480,

        show  : false,
        frame : false,

        backgroundColor: '#111'
    });

    win.on('ready-to-show', () => {
        win.show();
    });

    win.on('closed', () => {
        win = null;
    });

    win.loadURL(`file://${filepath}`);
});

app.on('windows-all-closed', () => {
    app.quit();
});
