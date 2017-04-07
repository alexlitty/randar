randar.component('bin-dialog', {
    computed: {
        bin: function() {
            return {
                name    : 'Master bin',
                folders : [
                    { name: 'Scenes', items: _.toArray(this.scenes), expanded: false },
                    { name: 'Models', items: _.toArray(this.models), expanded: false },
                    { name: 'Textures', items: _.toArray(this.textures), expanded: false }
                ]
            }
        }
    },

    template: `
        <dialog-box>
            <header class="drag-handle">Master bin</header>

            <bin-folder class="bin" :folder="bin" :root="true">
            </bin-folder>
        </dialog-box>
    `
});
