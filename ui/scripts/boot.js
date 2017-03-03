global._        = require('underscore');
global.Vue      = require('vue');
global.interact = require('interactjs');
global.randar   = require('./randar');

/**
 * Initialize the interface.
 */
randar.ready = function() {
    new Vue({
        el: document.getElementById('randar'),
        data: randar,
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
}
