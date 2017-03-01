(function() {
    /**
     * Component - Settings panel.
     */
    module.exports = randar.component('settings-panel',
        {
            template: `
                <div v-show="isSettingsSelected()">
                    <nav v-show="isSettingsSelected()">
                        <back-button v-bind:action="unselectSettings" />

                        <input-import></input-import>

                        <div id="engine-log"></div>
                    </nav>

                    <section></section>
                </div>
            `
        }
    );
})();
