(function() {
    randar.component('resource-dialog', {
        props: {
            resource: Object
        },

        template: `
            <dialog-box>
                <header class="drag-handle">{{ resource.name }}</header>
            </dialog-box>
        `
    });
})();
