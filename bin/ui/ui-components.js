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
            project  : function() { return app.$data.project; },
            scenes   : function() { return app.$data.resources.scenes; },
            models   : function() { return app.$data.resources.models; },
            textures : function() { return app.$data.resources.textures; },
            shaders  : function() { return app.$data.resources.shaders; }
        }
    }
);
