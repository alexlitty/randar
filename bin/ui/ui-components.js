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
 * Performs panel navigation.
 */
Component.Navigator = {
    methods: {
        navigate: function(panel) {
            app.$emit('navigate', panel); 
        }
    }
};

/**
 * A panel of the interface.
 */
Component.Panel = combine(
    Component.Navigator,
    {
        computed: {
            panelName       : function() { return null; },
            parentPanelName : function() { return null; },

            project   : function() { return randar.project; },
            resources : function() { return randar.resources; },

            scenes   : function() { return randar.resources.model; },
            models   : function() { return randar.resources.models; },
            textures : function() { return randar.resources.textures; },
            shaders  : function() { return randar.resources.shaders; }
        }
    }
);

/**
 * A panel dedicated to a resource.
 */
Component.ResourcePanel = combine(
    Component.Panel,
    {
        props: {
            category: String
        },

        computed: {
            currentPanel: function() { return randar.panel; }
        },

        template: `
            <nav v-show="currentPanel == category">
                <back-button v-on:click="navigate(parentPanelName)" />

                <ul v-bind:class="category">
                    <li v-for="(item, itemId) in resources[category]">
                        <slot name="item" :itemId="itemId" :item="item" />
                    </li>
                </ul>
            </nav>
        `
    }
);
