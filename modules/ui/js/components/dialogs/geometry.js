ui.component('dialog-geometry', {
    props: {
        item: Object
    },

    computed: {
        geo: function() {
            return this.item.object()
        }
    },

    methods: {
        onClose: function() {
            this.$emit('close');
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
        </div>
    `
});
