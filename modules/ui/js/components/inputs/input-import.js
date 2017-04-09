randar.component('input-import', {
    methods: {
        onClick: function() {
            randar.importResource();
        }
    },

    template: `
        <div class="button import" @click="onClick">
            Import Resource
        </div>
    `
});
