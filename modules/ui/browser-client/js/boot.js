const ipc      = require('electron').ipcRenderer;
const remote   = require('electron').remote;

const _        = require('underscore');
const glob     = require('glob');
const interact = require('interactjs');
const path     = require('path');
const Vue      = require('vue/dist/vue.common.js');

/**
 * Common functionality for all pages.
 */
global.ui = {
    paths: {
        js: path.join(__dirname, '..', 'js')
    },

    /**
     * Electron's BrowserWindow instance for this window.
     */
    browser: require('electron').remote.getCurrentWindow(),

    /**
     * Close the window.
     */
    exit: () => ui.browser.close(),

    /**
     * Project information.
     */
    project: remote.getGlobal('project')
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
    //ui.browser.setSize(screen.width, 32);

    document.body.addEventListener('contextmenu', function(event) {
        event.preventDefault();
        return false;
    });

    new Vue({
        el: document.getElementById('randar'),
        data: ui,
        methods: { }
    });
});
