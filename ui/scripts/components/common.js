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
            shaders  : function() { return randar.resources.shaders; },

            focusedResources : function() { return randar.focusedResources; }
        },

        methods: {
            getCurrentScene: function() {
                if (!this.focusedResources.length) {
                    return;
                }

                var resource = this.focusedResources[0];
                if (!resource || resource.resourceType !== 'scenes') {
                    return null;
                }

                return resource;
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
            },

            /**
             * Brings focus to the dialog for a resource.
             *
             * If the resource does not have a dialog, it is created.
             */
            focusResourceDialog: function(resource) {
                if (!randar.resourcesWithDialogs.includes(resource)) {
                    randar.resourcesWithDialogs.push(resource);
                }

                randar.focusedResources = [resource];
            }
        }
    };

    module.exports = common;
})();
