/**
 * A base, generic component for common functionality.
 */
var common = {
    computed: {
        ui    : function() { return ui; },

        project   : function() { return ui.project; },
        resources : function() { return ui.resources; },
        target    : function() { return ui.target; },

        scenes   : function() { return ui.resources.scenes; },
        models   : function() { return ui.resources.models; },
        textures : function() { return ui.resources.textures; },
        shaders  : function() { return ui.resources.shaders; },

        overlays         : function() { return ui.overlays; },
        focusedResources : function() { return ui.focusedResources; }
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
            return ui.target.settings;
        },

        selectSettings: function() {
            ui.target.settings = true;
        },

        unselectSettings: function() {
            ui.target.settings = false;
        },

        /**
         * Resource category targeting.
         */
        isResourceCategorySelected: function() {
            return !_.isNull(ui.target.resource.category);
        },

        setTargetResourceCategory: function(category) {
            ui.target.resource.category = category;
        },

        /**
         * Individual resource targeting.
         */
        isResourceSelected: function() {
            return this.isResourceCategorySelected()
                && !_.isNull(ui.target.resource.id);
        },

        setTargetResource: function(category, id) {
            ui.target.resource.category = category;
            ui.target.resource.id       = id;
        },

        clearTargetResource: function() {
            ui.target.resource.id = null;
        },

        /**
         * Brings focus to the dialog for a resource.
         *
         * If the resource does not have a dialog, it is created.
         */
        focusResourceDialog: function(resource) {
            if (!ui.resourcesWithDialogs.includes(resource)) {
                ui.resourcesWithDialogs.push(resource);
            }

            ui.focusedResources = [resource];
        },

        /**
         * Updates a resource on the UI, then patches the change into the
         * engine.
         */
        updateResource(resource, patch) {
            for (prop in patch) {
                this.$set(resource, prop, patch[prop]);
            }

            ui.engine.patchResource(resource.resourceType, resource.id, patch);
        }
    }
};

module.exports = common;
