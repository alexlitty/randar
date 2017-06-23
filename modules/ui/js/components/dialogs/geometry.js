ui.component('dialog-geometry', {
    props: {
        item: Object
    },

    data: function() {
        function generateVertexData() {
            return {
                position : { x: 0, y: 0, z: 0 },
                color    : { rInt: 255, gInt: 255, bInt: 255, aInt: 255 }
            }
        };

        return {
            appendShape: 'triangle',
            appendMenuItems: [
                { text: 'Append', contextMenu: [
                    [
                        { text: 'Triangle', action: function() {
                            this.appendShape = 'triangle';
                        }.bind(this)}
                    ]
                ]}
            ],

            appendedTriangle: [
                generateVertexData(),
                generateVertexData(),
                generateVertexData()
            ]
        }
    },

    computed: {
        geo: function() {
            return this.item.object()
        }
    },

    methods: {
        onClose: function() {
            this.$emit('close');
        },

        onAppend: function() {
            if (this.appendShape === 'triangle') {
                for (let i = 0; i < 3; i++) {
                    let vertex = this.randar.toVertex(this.appendedTriangle[i])
                    this.geo.append(vertex);
                }
            }

            this.item.dirty = true;
            this.project.save();
            this.$forceUpdate();
        }
    },

    template: `
        <div class="dialog draggable geometry">
            <menu-bar :text="item.name" :onClose="onClose"></menu-bar>

            <div class="info">
                <div v-if="geo.primitive === randar.Primitive_Point">
                    {{ geo.indices.count() }} Points
                </div>

                <div v-if="geo.primitive === randar.Primitive_Triangle">
                    {{ geo.indices.count() / 3 }} Triangles
                </div>
            </div>

            <menu-bar :items="appendMenuItems"></menu-bar>

            <div v-if="appendShape === 'triangle'">
                <div>Vertex #1</div>
                <input-vertex v-model="appendedTriangle[0]"></input-vertex>

                <div>Vertex #2</div>
                <input-vertex v-model="appendedTriangle[1]"></input-vertex>

                <div>Vertex #3</div>
                <input-vertex v-model="appendedTriangle[2]"></input-vertex>
            </div>

            <div class="button" @click="onAppend">Append</div>
        </div>
    `
});
