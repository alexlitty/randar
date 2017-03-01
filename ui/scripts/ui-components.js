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

/**
 * A table of resource metadata.
 */
Vue.component('resource-meta', {
    props: {
        resource: Object
    },

    computed: {
        metaProps: function() {
            if (this.resource.category === 'models') {
                return {
                    vertexCount: 'Vertex Count',
                    faceCount: 'Face Count'
                };
            }

            else if (this.resource.category === 'textures') {
                return {
                    type: 'Type',
                    width: 'Width',
                    height: 'Height'
                };
            }

            else {
                return { };
            }
        }
    },

    template: `
        <table class="metadata">
            <thead>
                <tr>
                    <th colspan="2">{{ resource.name }}</th>
                </tr>
            </thead>

            <tbody v-if="_.size(metaProps)">
                <tr v-for="(propTitle, propId) in metaProps">
                    <th>{{ propTitle }}</th>
                    <td>{{ resource[propId] }}</td>
                </tr>
            </tbody>
        </table>
    `
});

/**
 * An editor for models.
 */
Vue.component('editor-model', combine(
    Component.Common,
    {
        props: {
            model: Object
        },

        methods: {
            assignMeshTexture: function(category, textureId) {
                window.setModelMeshTexture(
                    this.model.id,
                    this.target.textureSlotId,
                    textureId
                );

                this.model.textures[this.target.textureSlotId] = textureId;
                this.target.textureSlotId = null;
            }
        },

        template: `
            <div>
                <table class="textures">
                    <thead>
                        <tr>
                            <th colspan="2">Textures</th>
                        </tr>
                    </thead>

                    <tbody v-if="model.hasTextures">
                        <tr class="clickable"
                         v-for="(textureId, textureSlotId) in model.textures"
                         @click="target.textureSlotId = textureSlotId">
                            <th>#{{ textureSlotId }}</th>

                            <td v-if="textures[textureId]">
                                {{ textures[textureId].name }}
                            </td>

                            <td v-else class="empty">Unassigned</td>
                        </tr>
                    </tbody>

                    <tbody v-else>
                        <tr>
                            <td>No texture slots</td>
                        </tr>
                    </tbody>
                </table>

                <input-resource
                    v-if="!_.isNull(target.textureSlotId)"
                    category="textures"
                    @close="target.textureSlotId = null"
                    @select="assignMeshTexture">
                </input-resource>
            </div>
        `
    }
));
global.Component = Component;

module.exports = { };
