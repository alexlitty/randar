/**
 * Combines two or more components together.
 */
function combine() {
    if (!arguments.length) {
        return { };
    }

    if (arguments.length == 1) {
        return arguments[0];
    }

    var result = { };
    for (component of arguments) {
        if (component.props) {
            result.props = _.extend(result.props || { }, component.props);
        }

        if (component.computed) {
            result.computed = _.extend(result.computed || { }, component.computed);
        }

        if (component.methods) {
            result.methods = _.extend(result.methods || { }, component.methods);
        }

        if (component.template) {
            result.template = component.template;
        }
    }
    return result;
}

/**
 * Partial components that may be extended and combined.
 */
var Component = { };

/**
 * A generic component for common functionality.
 */
Component.Common = {
    computed: {
        project   : function() { return randar.project; },
        resources : function() { return randar.resources; },
        target    : function() { return randar.target; },

        scenes   : function() { return randar.resources.model; },
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

        selectResourceCategory: function(category) {
            randar.target.resource.category = category;
        },

        unselectResourceCategory: function() {
            randar.target.resource.category = null;
        },

        /**
         * Individual resource targeting.
         */
        isResourceSelected: function() {
            return this.isResourceCategorySelected()
                && !_.isNull(randar.target.resource.id);
        },

        selectResource: function(category, id) {
            randar.target.resource.category = category;
            randar.target.resource.id       = id;
        },

        unselectResource: function() {
            randar.target.resource.id = null;
        }
    }
};

/**
 * A list of resources in a particular category.
 */
Component.ResourceList = combine(
    Component.Common,
    {
        props: {
            category: String
        },

        methods: {
            onResourceSelected: function(resourceId) {
                this.$emit('resourceSelected', this.category, resourceId);
            }
        },

        template: `
            <ul v-bind:class="category">
                <li v-for="(resource, resourceId) in resources[category]" v-on:click="onResourceSelected(resourceId)">
                    {{ resourceId }}
                </li>
            </ul>
        `
    }
);

Vue.component('resource-list', Component.ResourceList);

/**
 * A panel to show a resource list.
 */
Component.ResourceListPanel = combine(
    Component.Common,
    {
        props: {
            category: String
        },

        methods: {
            onClose: function() {
                this.$emit('close');
            },

            onResourceSelected: function(category, resourceId) {
                this.$emit('resourceSelected', category, resourceId);
            }
        },

        template: `
            <nav id="resource-list">
                <back-button v-bind:action="onClose" />

                <resource-list :category="category" @resourceSelected="onResourceSelected" />
            </nav>
        `
        //<!--<li v-for="(item, itemId) in resources[category]" v-on:click="selectResource(category, itemId)">-->
    }
);

Vue.component('resource-list-panel', Component.ResourceListPanel);

/**
 * A panel to interact with the currently targeted resource.
 */
Component.TargetResourcePanel = combine(
    Component.Common,
    {
        computed: {
            resource: function() {
                var result = this.getSelectedResource();
                result.hasTextures = !!(result.textures && result.textures.length);
                return result;
            }
        },

        template: `
            <nav id="target-resource" v-show="isResourceSelected()">
                <back-button :action="unselectResource" />

                <slot
                    v-bind:name="target.resource.category"
                    :resource="resource"
                    :textures="textures"
                    />
            </nav>
        `
    }
);
