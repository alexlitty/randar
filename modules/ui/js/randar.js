const glob = require('glob');

/**
 * Central object that organizes Randar UI functionality.
 */
global.randar = {
    common: require('./components/common'),

    /**
     * A reference to Electron's BrowserWindow instance for this window.
     */
    browser: require('electron').remote.getCurrentWindow(),

    /**
     * Close the UI and exit the program.
     */
    exit: () => randar.browser.close(),

    /**
     * Methods that bridge engine and UI functionality.
     */
    engine: {
        setMonitorTarget: (type, id) => {

        }
    },

    /**
     * Import a resource.
     */
    importResource: () => {

    },

    /** 
     * Handles an engine log message.
     */
    onEngineLog: function(message) {
        randar.log('[' + message.level + '] ' + message.contents);
    },  

    /** 
     * Submits a new log message to be shown on the interface.
     */
    log: function(message) {
        var div = document.createElement('div');
        div.innerHTML = message;

        var logElement = document.querySelector('#engine-log');
        logElement.insertBefore(div, logElement.firstChild);
    },  

    /** 
     * Retrieves all resources from the engine and shows them on the interface.
     */
    receiveData: function(data) {
        for (type in data) {
            if (type == "name") {
                randar.project.name = data[type];
            }   

            else if (_.isString(data[type])) {
                randar.resources[type] = data[type];
            }   

            else {
                for (item in data[type]) {
                    if (data[type][item]) {
                        data[type][item].id = item;
                        data[type][item].resourceType = type;
                        Vue.set(
                            randar.resources[type],
                            item,
                            data[type][item]
                        );
                    }
                }
            }
        }
    },

    /**
     * Project metadata.
     */
    project: {
        name: 'Untitled Film'
    },

    /**
     * Project resources.
     */
    resources: {
        scenes: { },
        models: { },
        textures: { },
        shaders: { }
    },

    /**
     * The current UI targets.
     */
    target: {
        settings: false,

        resource: {
            category : null,
            id       : null
        },

        textureSlotId: null
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
 * Add the component helper after randar.common is available.
 */
randar.component = require('./components/component');

/**
 * Initialize all available components, directives, and filters.
 */
for (dir of ['components', 'directives', 'filters']) {
    glob.sync(path.join(__dirname, dir, '**', '*.js')).forEach(filename => {
        require(filename);
    });
}
