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
    }
};

/**
 * A panel of the interface.
 */
Component.Panel = combine(
    Component.Common,
    {
        methods: {
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
                return !_.isNull(randar.target.resource.id);
            },

            selectResource: function(category, id) {
                randar.target.resource.category = category;
                randar.target.resource.id       = id;
            },

            unselectResource: function() {
                randar.target.resource.id = null;
            }
        }
    }
);

/**
 * A panel to list resources in a particular category.
 */
Component.ResourceListPanel = combine(
    Component.Panel,
    {
        computed: {
            category: function() {
                return this.target.resource.category;
            }
        },

        template: `
            <nav v-show="isResourceCategorySelected() && !isResourceSelected()">
                <back-button v-bind:action="unselectResourceCategory" />

                <ul v-bind:class="category">
                    <li v-for="(item, itemId) in resources[category]" v-on:click="selectResource(category, itemId)">
                        <slot name="item" :itemId="itemId" :item="item" />
                    </li>
                </ul>
            </nav>
        `
    }
);

/**
 * A panel to interact with the currently targeted resource.
 */
Component.TargetResourcePanel = combine(
    Component.Panel,
    {
        template: `
            <nav v-show="isResourceSelected()">
                <back-button v-bind:action="unselectResource" />
            </nav>
        `
    }
);
