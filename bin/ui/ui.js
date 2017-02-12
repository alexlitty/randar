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
    receiveData: function(data) {
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
     * Map engine-level methods.
     */
    setMonitorTarget: function(category, name) {
        window.setMonitorTarget(category, name);
    }
};


/**
 * Components - Buttons.
 */
Vue.component('back-button', combine(
    Component.Navigator,
    {
        props: {
            parentPanelName: String
        },

        template: `
            <ul class="back">
                <li v-on:click="navigate(parentPanelName)">&larrhk;</li>
            </ul>
        `
    }
));


/**
 * Components - Main panel.
 */
Vue.component('nav-main', combine(
    Component.Panel,
    {
        template: `
            <nav id="main">
                <ul>
                    <main-settings v-bind:project="project" />
                    <main-resource category="scenes" />
                    <main-resource category="models" />
                    <main-resource category="textures" />
                    <main-resource category="shaders" />
                </ul>
            </nav>
        `
    }
));

Vue.component('main-settings', combine(
    Component.Navigator,
    {
        props: {
            project: Object
        },

        template: `<li class="randar" v-on:click="navigate('settings')">{{ project.name }}</li>`,
    }
));

Vue.component('main-resource', combine(
    Component.Navigator,
    {
        props: {
            category: String
        },

        computed: {
            categoryName: function() {
                return toTitleCase(this.category);
            }
        },

        template: `
            <li v-bind:class="category" v-on:click="navigate(category)">{{ categoryName }}</li>
        `
    }
));


/**
 * Component - Settings panel.
 */
Vue.component('settings-panel', combine(
    Component.Panel,
    {
        computed: {
            currentPanel: function() { return randar.panel; }
        },

        template: `
            <nav v-show="currentPanel == 'settings'">
                <back-button v-bind:parentPanelName="parentPanelName" />

                <div id="import-resource" class="button">Import Resource</div>
                <div id="import-message"></div>

                <div id="engine-log"></div>
            </nav>
        `
    }
));


/**
 * Component - Resource panel.
 */
Vue.component('resource-panel', combine(
    Component.ResourcePanel,
    {

    }
));


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
        randar.panel = panel;
    });

    getElement('#import-resource').addEventListener('click', function() {
        var results = window.importResource();
        var message = results ? results.message : 'No file selected.';
        getElement('#import-message').innerHTML = message;
    });
}
