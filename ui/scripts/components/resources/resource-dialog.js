(function() {
    randar.component('resource-dialog', {
        props: {
            resource: Object
        },

        computed: {
            isFocused: function() {
                return this.randar.focusedResources.includes(this.resource);
            }
        },

        template: `
            <dialog-box :class="isFocused ? 'focused' : null">
                <header class="drag-handle" @click="focusResourceDialog(resource)">{{ resource.name }}</header>
                <resource-meta :resource="resource"></resource-meta>
            </dialog-box>
        `
    });
})();
