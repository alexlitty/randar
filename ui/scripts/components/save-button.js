(function() {
    var component = require('./component');

    /**
     * A button for saving the project.
     */
    module.exports = component('save-button',
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
