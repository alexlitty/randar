const _        = require('underscore');
const glob     = require('glob');
const interact = require('interactjs');
const path     = require('path');
const spawn    = require('child_process').spawn;
const Vue      = require('vue/dist/vue.common.js');

const nativeDialog = require('electron').remote.dialog;
const remote       = require('electron').remote;

const randar = require('../../wrapper');

/**
 * Common functionality for all pages.
 */
global.ui = {
    paths: {
        modules : path.join(__dirname, '..', '..'),
        js      : path.join(__dirname, '..', 'js')
    },

    nativeDialog: nativeDialog,

    /**
     * Parameters passed through the query string.
     */
    params: new URLSearchParams(window.location.search),

    /**
     * Electron's BrowserWindow instance for this window.
     */
    browser: remote.getCurrentWindow(),

    /**
     * Close the window.
     */
    exit: () => ui.browser.close(),

    /**
     * Project information.
     */
    project: randar.project(),

    /**
     * Dedicated area for page information.
     */
    page: { },

    /**
     * List of available monitor processes.
     */
    monitorProcesses: { },

    /**
     * Creates an item monitor.
     */
    monitor: (item) => {
        if (ui.monitorProcesses[item.id]) {
            return;
        }

        ui.project.save();
        let proc = spawn('node',
            [
                path.join(ui.paths.modules, 'monitor'),
                '--project', ui.project.directory().toString(),
                '--item', item.id
            ]
        );

        proc.on('close', () => {
            delete ui.monitorProcesses[item.id];
        });

        ui.monitorProcesses[item.id] = proc;
    }
};

ui.common    = require(path.join(ui.paths.js, 'components', 'common'));
ui.component = require(path.join(ui.paths.js, 'components', 'component'));

/**
 * Initialize all available components, directives, and filters.
 */
for (dir of ['components', 'directives', 'filters']) {
    let jsPath = path.join(__dirname, '..', 'js', dir, '**', '*.js');
    glob.sync(jsPath).forEach(filename => {
        require(filename);
    });
}

/**
 * Initialize the page.
 */
window.addEventListener('DOMContentLoaded', () => {
    document.body.addEventListener('contextmenu', function(event) {
        event.preventDefault();
        return false;
    });

    let basename = location.href.split(/[\\/]/).pop().replace('.html', '');
    if (basename.indexOf('?') > -1) {
        basename = basename.slice(0, basename.indexOf('?'));
    }
    require(path.join(ui.paths.js, 'pages', basename));

    if (ui.page.init) {
        ui.page.init();
    }

    new Vue({
        el: document.getElementById('randar'),
        data: ui,
        methods: { }
    });
});
