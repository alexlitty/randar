(function() {
    var common = require('./common');

    /**
     * Combines two or components together.
     *
     * If a single component is provided, the component is simply returned. If
     * no components are provided, an empty object is returned.
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
            if (component.data) {
                result.data = component.data;
            }

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
     * A component in our app.
     *
     * This is made available as randar.component for easy access.
     *
     * Essentially, this is a wrapper that initializes a new component into Vue
     * and extends it from the common component.
     *
     * First argument is the name of the component. Additional arguments are
     * combined into a single component.
     *
     * Returns the final composition of the component.
     */
    function component(name) {
        if (arguments.length <= 1) {
            return;
        }

        var result = combine.apply(
            this,
            [common].concat(
                [].slice.apply(arguments).slice(1)
            )
        );

        Vue.component(name, result);
        return result;
    }

    module.exports = component;
})();
