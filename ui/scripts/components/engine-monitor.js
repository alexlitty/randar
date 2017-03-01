(function() {
    var component = require('./component');

    /**
     * A dummy engine monitor, shown in debug mode.
     */
    module.exports = component('engine-monitor',
        {
            template: `
                <div id="engine-monitor" v-if="debug">
                    &lt; engine monitor &gt;
                </div>
            `
        }
    );
})();
