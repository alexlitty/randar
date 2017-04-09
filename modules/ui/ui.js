const {app, BrowserWindow} = require('electron');
const path = require('path');
const url = require('url');

var win;

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

    win.loadURL('file://' + __dirname + '/build/ui.html');
});

app.on('windows-all-closed', () => {
    app.quit();
});
