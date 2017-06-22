ui.component('dialog-geometry', {
    props: {
        item: Object
    },

    data: function() {
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
                { position: { x: 0, y: 0, z: 0 } }
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
                for (let i = 0; i < 1; i++) {
                    let position = this.appendedTriangle[i].position;

                    this.geo.append(
                        this.randar.vertex(this.randar.toVector(position))
                    );
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
                <input-vertex v-model="appendedTriangle[0]"></input-vertex>
            </div>

            <div class="button" @click="onAppend">Append</div>
        </div>
    `
});
