const {app, BrowserWindow} = require('electron');
const path = require('path');
const url = require('url');

var win;

function createWindow() {
    win = new BrowserWindow({
        width  : 800,
        height : 600
    });

    win.on('closed', () => {
        win = null;
    });
}

app.on('ready', createWindow);

app.on('windows-all-closed', () => {
    app.quit();
});
