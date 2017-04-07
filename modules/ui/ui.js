const {app, BrowserWindow} = require('electron');
const path = require('path');
const url = require('url');

var win;

app.on('ready', () => {
    win = new BrowserWindow({
        width  : 800,
        height : 600,

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

    win.loadURL('file://' + __dirname + '/build/ui.html');
});

app.on('windows-all-closed', () => {
    app.quit();
});
