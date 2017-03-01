(function() {
    /**
     * A button for saving the project.
     */
    module.exports = randar.component('save-button',
        {
            methods: {
                save: function() {
                    window.saveProject();
                }
            },

            template: `
                <div id="save" class="button" @click="save"></div>
            `
        }
    );
})();
