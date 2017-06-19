ui.component('dialog-geometry', {
    props: {
        item: Object
    },

    methods: {
        onClose: function() {
            this.$emit('close');
        }
    },

    template: `
        <div class="dialog draggable geometry">
            <menu-bar :text="item.name" :onClose="onClose"></menu-bar>
        </div>
    `
});