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
                    if (this.resource.category === 'models') {
                        return {
                            vertexCount: 'Vertex Count',
                            faceCount: 'Face Count'
                        };
                    }

                    else if (this.resource.category === 'textures') {
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
                <table class="metadata">
                    <thead>
                        <tr>
                            <th colspan="2">{{ resource.name }}</th>
                        </tr>
                    </thead>

                    <tbody v-if="_.size(metaProps)">
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
