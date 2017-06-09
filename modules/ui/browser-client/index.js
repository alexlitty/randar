const {app, BrowserWindow, globalShortcut} = require('electron');

const fs   = require('fs');
const ipc  = require('node-ipc');
const path = require('path');
const url  = require('url');

/**
 * Global reference to project information.
 */
global.project = {
    folders : { },
    items   : { }
};

/**
 * Emits an event to the master Randar process.
 */
global.emit = function(name, data) {
    data = data || { };
    data.e = name;

    process.send(data);
}

/**
 * Global list of open browsers.
 */
let browsers = { };

/**
 * Creates a new browser window.
 */
function createBrowserWindow(id, type) {
    let win = new BrowserWindow({
        minWidth  : 600,
        minHeight : 480,

        width  : 600,
        height : 480,

        show  : false,
        frame : false,

        transparent: true
    });

    win.on('ready-to-show', () => {
        win.show();
    });

    win.on('closed', () => {
        delete browsers[id];
    });

    let filepath = path.join(__dirname, 'build', `${type}.html`);
    win.loadURL(`file://${filepath}`);

    browsers[id] = win;
}

app.on('ready', () => {
    globalShortcut.register('F12', () => {
        let bw = BrowserWindow.getFocusedWindow();
        if (bw) {
            bw.toggleDevTools();
        }
    });

    process.on('message', function(data) {
        if (data.e === 'browser.open') {
            createBrowserWindow(data.id, data.type);
        }

        else if (data.e === 'browser.close') {
            delete browsers[data.id];
        }
    });

    process.send({ e: 'ready' });
});
