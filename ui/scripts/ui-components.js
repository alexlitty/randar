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
            <div v-show="isResourceSelected()">
                <nav id="target-resource">
                    <back-button :action="clearTargetResource" />

                    <resource-meta :resource="resource" />
                    <editor-model v-if="resource.category === 'models'" :model="resource" />
                </nav>

                <section>
                    <scene-timeline v-if="resource.category === 'scenes'">
                    </scene-timeline>
                </section>
            </div>
        `
    }
);

/**
 * A marker on a timeline.
 *
 * Indicates an action. Also used to create the timeline headers.
 */
Component.TimelineMarker = combine(
    {
        props: {
            markerId    : Number,
            zoom        : Number,
            frame       : Number,
            duration    : Number,
            significant : Boolean,
            selected    : Boolean
        },

        computed: {
            classes: function() {
                var result = ['marker'];

                if (this.significant) {
                    result.push('significant');
                }

                if (this.selected) {
                    result.push('selected');
                }

                return result;
            },

            style: function() {
                var width = (this.zoom * this.duration) - 1;
                if (width <= 0) {
                    width = 1;
                }

                return {
                    left  : this.zoom * this.frame,
                    width : width
                };
            }
        },

        methods: {
            onClick: function() {
                this.$emit('markerSelected', this.markerId);
            }
        },

        template: `
            <div :class="classes" :style="style" @click="onClick">
                <div>
                    <slot></slot>
                </div>
            </div>
        `
    }
);

Vue.component('timeline-marker', Component.TimelineMarker);

/**
 * A timeline for scene editing.
 */
Component.SceneTimeline = combine(
    Component.Common,
    {
        data: function() {
            return {
                selectedFrame: 0
            };
        },

        computed: {
            zoom: function() {
                return 75;
            },

            width: function() {
                return this.frames.length * this.zoom;
            },

            scene: function() {
                return this.getSelectedResource();
            },

            frames: function() {
                var result = [];

                for (var i = 0; i < 60; i++) {
                    result.push({
                        id: i,
                        significant: this.isFrameSignificant(i)
                    });
                }

                return result;
            }
        },

        methods: {
            isFrameSignificant: function(id) {
                return id % 5 === 0;
            },

            onGuideFrameSelected: function(frameId) {
                this.selectedFrame = frameId;
            }
        },

        template: `
            <div class="timeline">
                <div class="guide" :style="{ width: width }">
                    <header>&nbsp;</header>

                    <div class="markers">
                        <timeline-marker
                         v-for="frame in frames" :key="frame.id"
                         :markerId="frame.id"
                         :zoom="zoom"
                         :frame="frame.id"
                         :duration="1"
                         :significant="frame.significant"
                         :selected="selectedFrame === frame.id"
                         @markerSelected="onGuideFrameSelected">
                            <span v-if="frame.significant">{{ frame.id }}</span>
                        </timeline-marker>
                    </div>
                </div>

                <div class="items" :style="{ width: width }">
                    <div class="item" v-for="(object, objectId) in scene.objects">
                        <header>{{ objectId }}</header>

                        <div class="markers">
                            <timeline-marker
                             v-for="(action, actionId) in object.actions" :key="actionId"
                             :markerId="actionId"
                             :zoom="zoom"
                             :frame="action.frame"
                             :duration="action.duration">
                                Transform
                            </timeline-marker>
                        </div>
                    </div>
                </div>
            </div>
        `
    }
);

Vue.component('scene-timeline', Component.SceneTimeline);

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
