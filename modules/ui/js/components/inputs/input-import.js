ui.component('input-import', {
    methods: {
        onClick: function() {
            ui.importResource();
        }
    },

    template: `
        <div class="button import" @click="onClick">
            Import Resource
        </div>
    `
});
