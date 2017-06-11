ui.component('close-button', {
    methods: {
        onClick: function() {
            ui.exit();
        }
    },

    template: `
        <div class="close-button" @click="onClick()">x</div>
    `
});
