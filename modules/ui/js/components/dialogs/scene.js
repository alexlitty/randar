ui.component('dialog-scene', {
    props: {
        item: Object
    },

    computed: {
        scene: function() {
            return this.item.object();
        },

        frameCount: function() {
            return this.scene.calculateFrameCount();
        }
    },

    methods: {
        onClose: function() {
            this.$emit('close');
        }
    },

    template: `
        <div class="dialog draggable scene">
            <menu-bar :text="item.name" :onClose="onClose"></menu-bar>

            <div class="info">
                {{ frameCount }} Frames
                {{ scene.actions.length }} Actions
            </div>
        </div>
    `
});
