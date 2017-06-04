const ipc      = require('electron').ipcRenderer;
const remote   = require('electron').remote;

const _        = require('underscore');
const interact = require('interactjs');
const path     = require('path');
const Vue      = require('vue/dist/vue.common.js');

/**
 * Common functionality for all pages.
 */
global.ui = {
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
