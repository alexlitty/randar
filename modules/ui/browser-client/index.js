const {app, BrowserWindow} = require('electron');

const fs   = require('fs');
const ipc  = require('node-ipc');
const path = require('path');
const url  = require('url');

/**
 * Global list of open browsers.
 */
let browsers = { };

/**
 * Creates a new browser window.
 */
function createBrowserWindow(id, type) {
    if (type === 'main') {
        type = 'ui';
    }

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

    let filepath = path.join(__dirname, 'build', `${type}.html`);
    win.loadURL(`file://${filepath}`);

    browsers[id] = win;
}

app.on('ready', () => {
    process.send({ e: 'ready' });

    process.on('message', function(data) {
        if (data.e === 'browser.open') {
            createBrowserWindow(data.id, data.type);
        }

        else if (data.e === 'browser.close') {
            delete browsers[data.id];
        }
    });
});
