global._        = require('underscore');
global.Vue      = require('vue');
global.interact = require('interactjs');
global.randar   = require('./randar');

/**
 * Initialize the interface.
 */
randar.ready = function() {
    interact('.draggable')
        .draggable({
            inertia: true,

            restrict: {
                restriction : 'parent',
                endOnly     : true,
                elementRect : { top: 0, left: 0, bottom: 1, right: 1 }
            },

            onmove: function(event) {
                var target = event.target,
                    x = (parseFloat(target.getAttribute('data-x')) || 0) + event.dx,
                    y = (parseFloat(target.getAttribute('data-y')) || 0) + event.dy;

                target.style.transform = 'translate(' + x + 'px, ' + y + 'px)';
                target.setAttribute('data-x', x);
                target.setAttribute('data-y', y);
            }
        })
        .allowFrom('.drag-handle')
        .styleCursor(false);

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
