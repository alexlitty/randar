(function() {
    randar.component('bin-dialog', {
        computed: {
            bin: function() {
                return {
                    name    : 'Master bin',
                    folders : [
                        { name: 'Scenes', items: _.toArray(this.scenes) },
                        { name: 'Models', items: _.toArray(this.models) },
                        { name: 'Textures', items: _.toArray(this.textures) }
                    ]
                }
            }
        },

        template: `
            <dialog-box>
                <header class="drag-handle">Master bin</header>

                <bin-folder class="bin" :contents="bin" :root="true">
                </bin-folder>
            </dialog-box>
        `
    });
})();
