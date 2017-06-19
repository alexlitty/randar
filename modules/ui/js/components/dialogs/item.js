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
            <dialog-geometry :geometry="item.object()" @close="onClose">
            </dialog-geometry>
        </div>
    `
});
