var Vue = require('vue');
global._ = require('underscore');
var randar = require('./randar');
var app;

/**
 * Initialize the interface.
 */
randar.ready = function() {
    app = new Vue({
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

    /*document.querySelector('#import-resource').addEventListener('click', function() {
        var results = window.importResource();
        var message = results ? results.message : 'No file selected.';
        document.querySelector('#import-message').innerHTML = message;
    });*/
}
