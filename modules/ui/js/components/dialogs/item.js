ui.component('dialog-item', {
    props: {
        item: Object
    },

    methods: {
        onClose: function() {
            this.$delete(this.itemDialogs, this.item.id);
        }
    },

    template: `
        <div v-if="item.kind === 'geometry'">
            <dialog-geometry :item="item" @close="onClose">
            </dialog-geometry>
        </div>

        <div v-else-if="item.kind === 'scene'">
            <dialog-scene :item="item" @close="onClose">
            </dialog-scene>
        </div>
    `
});
