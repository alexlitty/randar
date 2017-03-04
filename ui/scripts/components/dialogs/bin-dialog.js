(function() {
    randar.component('bin-dialog', {
        data: function () {
            return {
                items: [
                    { text: 'Master bin' }
                ],

                objects: [
                    _.mapObject(this.textures, function(texture, textureId) {
                        return {
                            id   : textureId,
                            text : texture.name
                        };
                    })
                ]
            }
        },

        template: `
            <dialog-box>
                <header class="drag-handle">Master bin</header>
            </dialog-box>
        `
    });
})();
