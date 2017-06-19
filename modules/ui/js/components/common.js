/**
 * A base, generic component for common functionality.
 */
let common = {
    computed: {
        ui        : function() { return ui; },
        project   : function() { return ui.project; },

        itemDialogs : function() { return ui.itemDialogs; }
    },

    methods: {
    }
};

module.exports = common;
