const path   = require('path');
const spawn  = require('child_process').spawn;

// Prepare Randar and UI functionality.
global.randar = require('../wrapper');

randar.ui = {
    views   : [ ],
    project : randar.project()
};

require('./Browser.js');
require('./View.js');

// List of open views.
let views = [ ];

// Start browser client.
let electronPath = path.resolve(path.join(
    __dirname, '..', '..', 'node_modules', 'electron', 'dist', 'electron'
));

randar.ui.clients = {
    browsers : spawn(electronPath, ['./browser-client', '--enable-transparent-visuals', '--disable-gpu'], {
        cwd   : __dirname,
        stdio : ['inherit', 'inherit', 'inherit', 'ipc']
    })
};

randar.ui.clients.browsers.on('message', (data) => {
    if (data.e === 'ready') {
        randar.ui.views.push(new randar.ui.View('main'));
    }

    else if (data.e === 'view.open') {
        randar.ui.views.push(new randar.ui.View(data.type, data.params || { }));
    }

    else {
        console.warn('Ignoring unknown event:', data);
    }
});
    
randar.ui.clients.browsers.on('close', () => {
    process.exit(0);
});
