var app;

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
     * The current UI targets.
     */
    target: {
        settings: false,

        resource: {
            category : null,
            id       : null
        },

        textureSlotId: null
    }
};


/**
 * Components - Buttons.
 */
Vue.component('back-button', combine(
    {
        props: {
            action: Function
        },

        template: `
            <ul class="back">
                <li v-on:click="action()">&larrhk;</li>
            </ul>
        `
    }
));


/**
 * Components - Main panel.
 */
Vue.component('nav-main', combine(
    Component.Common,
    {
        template: `
            <nav id="main" v-show="isNothingSelected()">
                <ul>
                    <li class="randar" v-on:click="selectSettings()">
                        {{ project.name }}
                    </li>

                    <li v-for="category in ['scenes', 'models', 'textures', 'shaders']"
                        v-bind:class="category" v-on:click="target.resource.category = category">
                        {{ category | titlecase }}
                    </li>
                </ul>
            </nav>
        `
    }
));

/**
 * Component - Settings panel.
 */
Vue.component('settings-panel', combine(
    Component.Common,
    {
        template: `
            <nav v-show="isSettingsSelected()">
                <back-button v-bind:action="unselectSettings" />

                <div id="import-resource" class="button">Import Resource</div>
                <div id="import-message"></div>

                <div id="engine-log"></div>
            </nav>
        `
    }
));

/**
 * Component - Resources.
 */
Vue.component('target-resource-panel', combine(
    Component.TargetResourcePanel,
    {

    }
));

/**
 * Vue filters.
 */
Vue.filter('titlecase', function(value) {
    if (!_.isString(value) || !value.length) {
        return value;
    }

    return value.charAt(0).toUpperCase() + value.slice(1);
});

/**
 * Initialize the interface.
 */
randar.ready = function() {
    app = new Vue({
        el: '#randar',
        data: _.extend(randar, Component.Common),
        methods: Component.Common.methods,
        watch: {
            target: {
                deep: true,
                handler: function(value, oldValue) {
                    window.setMonitorTarget(
                        value.resource.category,
                        value.resource.id
                    );
                }
            }
        }
    });

    getElement('#import-resource').addEventListener('click', function() {
        var results = window.importResource();
        var message = results ? results.message : 'No file selected.';
        getElement('#import-message').innerHTML = message;
    });
}
