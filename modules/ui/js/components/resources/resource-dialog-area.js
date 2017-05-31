ui.component('resource-dialog-area', {
    data: function() {
        return {
            resources        : ui.resourcesWithDialogs,
            focusedResources : ui.focusedResources
        };
    },

    template: `
        <div class="dialog-area">
            <resource-dialog v-for="(resource, resourceId) in resources"
             :key="resourceId"
             :resource="resource"
             :class="focusedResources.includes(resource) ? 'focused' : null">
            </resource-dialog>
        </div>
    `
});
