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
                var target = event.target;
                var x, y;

                if (target.getAttribute('data-x') === null) {
                    var result = /^matrix\(1, 0, 0, 1, (\d+), (\d+)\)$/.exec(
                        getComputedStyle(target).transform
                    );

                    if (result) {
                        x = parseFloat(result[1]) || 0;
                        y = parseFloat(result[2]) || 0;
                    } else {
                        x = y = 0;
                    }
                }
                
                else {
                    x = parseFloat(target.getAttribute('data-x')) || 0;
                    y = parseFloat(target.getAttribute('data-y')) || 0;
                }

                x += event.dx;
                y += event.dy;

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
