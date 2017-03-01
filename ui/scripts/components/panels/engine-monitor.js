(function() {
    /**
     * A dummy engine monitor, shown in debug mode.
     */
    module.exports = randar.component('engine-monitor',
        {
            template: `
                <div id="engine-monitor" v-if="debug">
                    &lt; engine monitor &gt;
                </div>
            `
        }
    );
})();
