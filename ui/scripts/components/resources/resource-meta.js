(function() {
    /**
     * A table of resource metadata.
     */
    module.exports = randar.component('resource-meta',
        {
            props: {
                resource: Object
            },

            computed: {
                metaProps: function() {
                    if (this.resource.resourceType === 'models') {
                        return {
                            vertexCount: 'Vertex Count',
                            faceCount: 'Face Count'
                        };
                    }

                    else if (this.resource.resourceType === 'textures') {
                        return {
                            type: 'Type',
                            width: 'Width',
                            height: 'Height'
                        };
                    }

                    else {
                        return { };
                    }
                }
            },

            template: `
                <table class="metadata" v-if="_.size(metaProps)">
                    <tbody>
                        <tr v-for="(propTitle, propId) in metaProps">
                            <th>{{ propTitle }}</th>
                            <td>{{ resource[propId] }}</td>
                        </tr>
                    </tbody>
                </table>
            `
        }
    );
})();
