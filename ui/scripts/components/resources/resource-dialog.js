(function() {
    randar.component('resource-dialog', {
        props: {
            resource: Object
        },

        data: function() {
            return {
                isEditingName : false,
                newName       : this.resource.name
            }
        },

        computed: {
            isFocused: function() {
                return this.randar.focusedResources.includes(this.resource);
            }
        },

        methods: {
            submitName: function() {
                this.updateResource(this.resource, {
                    name : this.newName
                });

                this.isEditingName = false;
            }
        },

        template: `
            <dialog-box class="resource" :class="isFocused ? 'focused' : null">
                <header v-if="!isEditingName" class="drag-handle"
                 @click="focusResourceDialog(resource)"
                 @dblclick="isEditingName = true">
                    {{ resource.name }}
                </header>

                <header v-else>
                    <form @submit.prevent="submitName">
                        <input type="text" v-model="newName" />
                        <input type="submit" value=""></span>
                    </form>
                </header>

                <resource-meta :resource="resource"></resource-meta>
            </dialog-box>
        `
    });
})();
