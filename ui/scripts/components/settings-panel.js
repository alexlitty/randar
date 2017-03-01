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

                        <div id="import-resource" class="button">Import Resource</div>
                        <div id="import-message"></div>

                        <div id="engine-log"></div>
                    </nav>

                    <section></section>
                </div>
            `
        }
    );
})();
