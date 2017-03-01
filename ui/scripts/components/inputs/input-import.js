(function() {
    randar.component('input-import',
        {
            methods: {
                onClick: function() {
                    window.importResource();
                }
            },

            template: `
                <div class="button import" @click="onClick">
                    Import Resource
                </div>
            `
        }
    );
})();
