/**
 * Object that contains the Randar UI "app" functionality.
 */
var randar = {
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

        var logElement = getElement('#engine-log');
        logElement.insertBefore(div, logElement.firstChild);
    },

    /**
     * Retrieves all resources from the engine and shows them on the interface.
     */
    updateResources: function() {
        var data = JSON.parse(window.getResources());

        for (type in data) {
            if (type == "name") {
                randar.project.name = data[type];
            }

            else if (isString(data[type])) {
                randar.resources[type] = data[type];
            }

            else {
                for (item in data[type]) {
                    randar.resources[type][item] = data[type][item];
                }
            }
        }

        /*// Update project name.
        var projectInfo = getElement('#main .randar');
        if (randar.resources.name) {
            projectInfo.innerHTML = randar.resources.name;
        } else {
            projectInfo.innerHTML = 'Untitled Project';
        }

        // Update list elements.
        var texturesList = getElement('#objects .textures');
        clearElement(texturesList);
        for (textureName in randar.resources.textures) {
            var element = document.createElement('li');
            element.innerHTML = textureName;

            element.addEventListener('click', function(textureName) {
                randar.setMonitorTarget('textures', textureName);
            }.bind(this, textureName));
            texturesList.appendChild(element);
        }

        var modelsList = getElement('#objects .models');
        clearElement(modelsList);
        for (modelName in randar.resources.models) {
            var element = document.createElement('li');
            element.innerHTML = modelName;

            element.addEventListener('click', function(modelName) {
                randar.setMonitorTarget('models', modelName);
            }.bind(this, modelName));
            modelsList.appendChild(element);
        }*/
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
        models: { },
        textures: { },
        shaders: { }
    },

    /**
     * The current panel.
     */
    panel: null,

    /**
     * "Navigates" to a different panel.
     */
    navigate(panel) {
        randar.panel = panel;
    },

    /**
     * Map engine-level methods.
     */
    setMonitorTarget: function(category, name) {
        window.setMonitorTarget(category, name);
    }
};


/**
 * Generic helpers.
 */
function getElement(query) {
    return document.querySelector(query);
}

function getElements(query) {
    return document.querySelectorAll(query);
}

function hideElement(element) {
    element.classList.add('hidden');
}

function showElement(element) {
    element.classList.remove('hidden');
}

function isString(value) {
    return typeof value === 'string' || value instanceof String;
}

function clearElement(element) {
    element.innerHTML = '';
}

function toTitleCase(value) {
    if (!isString(value) || !value.length) {
        return value;
    }

    return value.charAt(0).toUpperCase() + value.slice(1);
}


/**
 * Vue components.
 */
Vue.component('nav-main', {
    props: {
        project: Object
    },

    template: `
        <nav id="main" v-on:test="console.log('hmm')">
            <ul>
                <main-settings v-bind:project="project" />
                <main-resource category="scenes" />
                <main-resource category="models" />
                <main-resource category="textures" />
                <main-resource category="shaders" />
            </ul>
        </nav>
    `
});

Vue.component('main-settings', {
    props: {
        project: Object
    },

    methods: {
        navigate: function() { app.$emit('navigate', 'settings'); }
    },

    template: `<li class="randar" v-on:click="navigate">{{ project.name }}</li>`,
});

Vue.component('main-resource', {
    props: {
        category: String
    },

    computed: {
        categoryName: function() {
            return toTitleCase(this.category);
        }
    },

    methods: {
        navigate: function() { app.$emit('navigate', this.category); }
    },

    template: `
        <li v-bind:class="category" v-on:click="navigate">{{ categoryName }}</li>
    `
});


/**
 * Initialize the interface.
 */
var app;
randar.ready = function() {
    app = new Vue({
        el: '#randar',
        data: randar,
        methods: randar
    });

    app.$on('navigate', function(panel) {
        console.log('navigated to ' + panel);
    });

    getElement('#import-resource').addEventListener('click', function() {
        var results = window.importResource();
        randar.updateResources();

        var message = results ? results.message : 'No file selected.';
        getElement('#import-message').innerHTML = message;
    });

    randar.updateResources();
}
