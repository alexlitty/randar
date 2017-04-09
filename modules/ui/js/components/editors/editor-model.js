/**
 * An editor for models.
 */
randar.component('editor-model', {
    props: {
        model: Object
    },

    methods: {
        assignMeshTexture: function(category, textureId) {
            randar.engine.setModelMeshTexture(
                this.model.id,
                this.target.textureSlotId,
                textureId
            );

            this.model.textures[this.target.textureSlotId] = textureId;
            this.target.textureSlotId = null;
        }
    },

    template: `
        <div>
            <table class="textures">
                <thead>
                    <tr>
                        <th colspan="2">Textures</th>
                    </tr>
                </thead>

                <tbody v-if="model.hasTextures">
                    <tr class="clickable"
                     v-for="(textureId, textureSlotId) in model.textures"
                     @click="target.textureSlotId = textureSlotId">
                        <th>#{{ textureSlotId }}</th>

                        <td v-if="textures[textureId]">
                            {{ textures[textureId].name }}
                        </td>

                        <td v-else class="empty">Unassigned</td>
                    </tr>
                </tbody>

                <tbody v-else>
                    <tr>
                        <td>No texture slots</td>
                    </tr>
                </tbody>
            </table>

            <input-resource
                v-if="!_.isNull(target.textureSlotId)"
                category="textures"
                @close="target.textureSlotId = null"
                @select="assignMeshTexture">
            </input-resource>
        </div>
    `
});
