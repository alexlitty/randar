var _ = require('underscore');
var Vue = require('vue');
require('./ui-components');
var randar = require('./randar');
var app;

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
            <div v-show="isNothingSelected()">
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

                <section class="info">
                    Welcome to Randar.
                </section>
            </div>
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
            <div v-show="isSettingsSelected()">
                <nav v-show="isSettingsSelected()">
                    <back-button v-bind:action="unselectSettings" />

                    <div id="import-resource" class="button">Import Resource</div>
                    <div id="import-message"></div>

                    <div id="engine-log"></div>
                </nav>

                <section></section>
            </div>
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
        el: document.getElementById('randar'),
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

    /*document.querySelector('#import-resource').addEventListener('click', function() {
        var results = window.importResource();
        var message = results ? results.message : 'No file selected.';
        document.querySelector('#import-message').innerHTML = message;
    });*/
}
if ((window.location.search || '').indexOf('debug') > -1) {
    randar.debug = true;

    window.saveProject = function() {
        console.info("Project would be saved");
    }

    window.setMonitorTarget = function(category, name) {
        if (_.isNull(name) || _.isNull(category)) {
            console.info("Set monitor target to nothing");
        }
        
        else {
            console.info("Set monitor target to '" + category + "' #" + name);
        }
    }

    window.importResource = function() {
        console.info("Resource would be imported");
    }

    window.createResource = function(category) {
        console.info("New resource would be created in " + category);
    }

    window.setModelMeshTexture = function(modelId, slotId, textureId) {
        console.info("Model #" + modelId + ", texture slot #" + slotId + " would be set to texture #" + textureId);
    }

    randar.receiveData({
        name: 'Test film',

        textures: {
            0: {
                name: "Example texture",

                type: "rgba",
                width: 200,
                height: 140
            }
        },

        models: {
            0: {
                name: "Example model",

                vertexCount: 1016,
                faceCount: 2464,

                textures: [0, null, 0]
            }
        },

        scenes: {
            0: {
                name: "Example scene",

                objects: {
                    0: {
                        modelId: 0,
                        actions: [
                            {
                                type     : "transform",
                                frame    : 3,
                                duration : 4,

                                transform: {
                                    position: {
                                        x : 0.5,
                                        y : 0,
                                        z : 0
                                    },

                                    rotation: {
                                        axis: {
                                            x : 0,
                                            y : 1,
                                            z : 0
                                        },

                                        angle: 0.75
                                    }
                                }
                            }
                        ]
                    }
                }
            }
        }

    });

    window.addEventListener('load', function() {
        randar.ready();
    });
}
