/**
 * A generic component for common functionality.
 */
(function() {
     var common = {
        computed: {
            randar    : function() { return randar; },

            debug     : function() { return randar.debug; },
            project   : function() { return randar.project; },
            resources : function() { return randar.resources; },
            target    : function() { return randar.target; },

            scenes   : function() { return randar.resources.scenes; },
            models   : function() { return randar.resources.models; },
            textures : function() { return randar.resources.textures; },
            shaders  : function() { return randar.resources.shaders; }
        },

        methods: {
            getSelectedResource: function() {
                if (!this.isResourceSelected()) {
                    return { };
                }

                var resource = this.target.resource;
                return this.resources[resource.category][resource.id];
            },

            isNothingSelected: function() {
                return !this.isSettingsSelected()
                    && !this.isResourceCategorySelected()
                    && !this.isResourceSelected();
            },

            /**
             * Settings targeting.
             */
            isSettingsSelected: function() {
                return randar.target.settings;
            },

            selectSettings: function() {
                randar.target.settings = true;
            },

            unselectSettings: function() {
                randar.target.settings = false;
            },

            /**
             * Resource category targeting.
             */
            isResourceCategorySelected: function() {
                return !_.isNull(randar.target.resource.category);
            },

            setTargetResourceCategory: function(category) {
                randar.target.resource.category = category;
            },

            /**
             * Individual resource targeting.
             */
            isResourceSelected: function() {
                return this.isResourceCategorySelected()
                    && !_.isNull(randar.target.resource.id);
            },

            setTargetResource: function(category, id) {
                randar.target.resource.category = category;
                randar.target.resource.id       = id;
            },

            clearTargetResource: function() {
                randar.target.resource.id = null;
            }
        }
    };

    module.exports = common;
})();
