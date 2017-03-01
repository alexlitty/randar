var _ = require('underscore');
global._ = _;
var Vue = require('vue');
require('./helpers');

/**
 * Combines two or more components together.
 */
global.combine = function() {
    if (!arguments.length) {
        return { };
    }

    if (arguments.length == 1) {
        return arguments[0];
    }

    var result = { };
    for (component of arguments) {
        if (!component) {
            continue;
        }

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
 * Partial components that may be extended and combined.
 */
var Component = { };

/**
 * A generic component for common functionality.
 */
Component.Common = require('./components/common');

global.Component = Component;

module.exports = { };
