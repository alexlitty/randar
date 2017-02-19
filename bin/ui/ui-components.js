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
            onSelect: function(resourceId) {
                this.$emit('select', this.category, resourceId);
            }
        },

        template: `
            <ul v-bind:class="category">
                <li v-for="(resource, resourceId) in resources[category]" v-on:click="onSelect(resourceId)">
                    {{ resourceId }}
                </li>
            </ul>
        `
    }
);

Vue.component('resource-list', Component.ResourceList);

/**
 * An input to select a resource.
 */
Component.InputResource = combine(
    Component.Common,
    {
        props: {
            category: String
        },

        methods: {
            onClose: function() {
                this.$emit('close');
            },

            onSelect: function(category, resourceId) {
                this.$emit('select', category, resourceId);
            }
        },

        template: `
            <nav id="resource-list">
                <back-button v-bind:action="onClose" />

                <resource-list :category="category" @select="onSelect" />
            </nav>
        `
    }
);

Vue.component('input-resource', Component.InputResource);

/**
 * A panel to interact with the currently targeted resource.
 */
Component.TargetResourcePanel = combine(
    Component.Common,
    {
        computed: {
            resource: function() {
                var result = this.getSelectedResource();
                result.category = _.clone(this.target.resource.category);
                result.hasTextures = !!(result.textures && result.textures.length);
                return result;
            }
        },

        template: `
            <nav id="target-resource" v-show="isResourceSelected()">
                <back-button :action="clearTargetResource" />

                <resource-meta :resource="resource" />
                <editor-model :model="resource" />
            </nav>
        `
    }
);

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
