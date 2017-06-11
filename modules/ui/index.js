const {app, BrowserWindow, globalShortcut} = require('electron');
const randar = require('../wrapper');

const fs   = require('fs');
const ipc  = require('node-ipc');
const path = require('path');
const url  = require('url');

/**
 * Global reference to project information.
 */
global.project = randar.project();

/**
 * Global list of open browsers.
 */
let browsers = [ ];

/**
 * Creates a new browser window.
 */
global.createBrowserWindow = (type, params) => {
    let win = new BrowserWindow({
        minWidth  : 32,
        minHeight : 32,

        show  : false,
        frame : false,
    });

    win.on('ready-to-show', () => {
        win.show();
    });

    win.on('closed', () => {
        let idx = browsers.indexOf(win);
        if (idx > -1) {
            browsers.slice(idx, 1);
        }
    });

    let filepath = path.join(__dirname, 'build', `${type}.html`) + '?';
    for (paramId in params) {
        filepath += `${paramId}=${params[paramId]}&`;
    }

    win.loadURL(`file://${filepath}`);
    browsers.push(win);
}

app.on('ready', () => {
    globalShortcut.register('F12', () => {
        let bw = BrowserWindow.getFocusedWindow();
        if (bw) {
            bw.toggleDevTools();
        }
    });

    createBrowserWindow('main', { });
    createBrowserWindow('bins', { });
});
