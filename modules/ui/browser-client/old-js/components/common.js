/**
 * A base, generic component for common functionality.
 */
var common = {
    computed: {
        ui        : function() { return ui; },
        project   : function() { return ui.project; },

        overlays  : function() { return ui.overlays; }
    },

    methods: {
    }
};

module.exports = common;
