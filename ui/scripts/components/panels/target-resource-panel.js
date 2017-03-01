(function() {
    /**
     * A panel to interact with the currently targeted resource.
     */
    module.exports = randar.component('target-resource-panel',
        {
            computed: {
                resource: function() {
                    var result = this.getSelectedResource();
                    result.category = _.clone(this.target.resource.category);
                    result.hasTextures = !!(result.textures && result.textures.length);
                    return result;
                }
            },

            template: `
                <div v-show="isResourceSelected()">
                    <nav id="target-resource">
                        <back-button :action="clearTargetResource" />

                        <resource-meta :resource="resource" />
                        <editor-model v-if="resource.category === 'models'" :model="resource" />
                    </nav>

                    <section>
                        <scene-timeline v-if="resource.category === 'scenes'">
                        </scene-timeline>
                    </section>
                </div>
            `
        }
    );
})();
