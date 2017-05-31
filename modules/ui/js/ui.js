const glob = require('glob');

/**
 * Central object that organizes Randar UI functionality.
 */
global.ui = {
    common: require('./components/common'),

    /**
     * A reference to Electron's BrowserWindow instance for this window.
     */
    browser: require('electron').remote.getCurrentWindow(),

    /**
     * Close the UI and exit the program.
     */
    exit: () => ui.browser.close(),

    /**
     * Import a resource.
     */
    importResource: () => {
        console.log('importing resource');
    },

    /**
     * Project metadata.
     */
    project: {
        name: 'Untitled Film'
    },

    /**
     * Overlays that should be displayed.
     */
    overlays: { },

    /**
     * Collection of resources that have an open dialog.
     */
    resourcesWithDialogs: [],

    /**
     * Resources whose dialogs should be focused.
     */
    focusedResources: []
};

/**
 * Add the component helper after ui.common is available.
 */
ui.component = require('./components/component');

/**
 * Initialize all available components, directives, and filters.
 */
for (dir of ['components', 'directives', 'filters']) {
    glob.sync(path.join(__dirname, dir, '**', '*.js')).forEach(filename => {
        require(filename);
    });
}
