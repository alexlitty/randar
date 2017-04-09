const {app}    = require('electron').remote;
const path     = require('path');

const _        = require('underscore');
const interact = require('interactjs');
const Vue      = require('vue/dist/vue.common.js');

require(path.join(app.getAppPath(), 'js', 'randar'));

/**
 * Initialize the interface.
 */
window.addEventListener('DOMContentLoaded', () => {
    randar.browser.setSize(screen.width, screen.height);

    document.body.addEventListener('contextmenu', function(event) {
        event.preventDefault();
        return false;
    });

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
        methods: randar.common.methods,
        watch: {
            focusedResources: function(value) {
                if (!value.length) {
                    randar.engine.setMonitorTarget();
                }

                else {
                    randar.engine.setMonitorTarget(
                        value[0].resourceType,
                        value[0].id
                    );
                }
            }
        }
    });
});
