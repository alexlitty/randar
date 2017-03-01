(function() {
    var component = require('./component');

    /**
     * Components - Buttons.
     */
    module.exports = component('back-button',
        {
            props: {
                action: Function
            },

            template: `
                <ul class="back">
                    <li v-on:click="action()">&larrhk;</li>
                </ul>
            `
        }
    );
})();
