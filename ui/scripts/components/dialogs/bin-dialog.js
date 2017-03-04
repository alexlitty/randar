(function() {
    randar.component('bin-dialog', {
        computed: {
            bin: function() {
                return [
                    { name: 'Scenes', items: this.scenes },
                    { name: 'Models', items: this.models },
                    { name: 'Textures', items: this.textures }
                ];
            }
        },

        template: `
            <dialog-box>
                <header class="drag-handle">Master bin</header>

                <div class="bin">
                    <div class="folder" v-for="folder in bin">
                        <div class="name">{{ folder.name }}</div>
                        <div class="item" v-for="item in folder.items">
                            {{ item.name }}
                        </div>
                    </div>
                </div>
            </dialog-box>
        `
    });
})();
