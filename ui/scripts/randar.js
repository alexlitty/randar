(function() {
    var component = require('./components/component');

    /**
     * Central object that organizes Randar UI functionality.
     */
    var randar = {
        component: component,

        /** 
         * Debug mode toggle.
         */
        debug: false,

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
        }
    };

    module.exports = randar;
})();
