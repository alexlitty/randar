global._        = require('underscore');
global.Vue      = require('vue');
global.interact = require('interactjs');
global.randar   = require('./randar');

/**
 * Initialize draggable elements.
 */
interact('.draggable')
    .draggable({
        intertia: true,

        restrict: {
            restriction : 'parent',
            endOnly     : true,
            elementRect : { top: 0, left: 0, bottom: 1, right: 1 }
        },

        autoScroll: true
    });

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
