ui.component('dialog-geometry', {
    props: ['geometry'],

    methods: {
        onClose: function() {
            this.$emit('close');
        }
    },

    template: `
        <div class="dialog geometry">
            <menu-bar :onClose="onClose"></menu-bar>
        </div>
    `
});
