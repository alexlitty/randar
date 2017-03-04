(function() {
    randar.component('bin-folder', {
        props: {
            root   : Boolean,
            folder : Object
        },

        data: function() {
            return {
                expanded: this.root || !!this.folder.expanded
            };
        },

        methods: {
        },

        template: `
            <div class="folder">
                <div v-if="!root"
                 :class="['name', expanded ? 'expanded' : null]"
                 @click="expanded = !expanded">
                    {{ folder.name }}
                </div>

                <div v-if="expanded">
                    <bin-folder v-for="(subfolder, subfolderId) in folder.folders"
                     :key="subfolderId"
                     :folder="subfolder">
                    </bin-folder>

                    <div class="item" v-for="(item, itemId) in folder.items"
                     :key="itemId">
                        <div class="name">{{ item.name }}</div>
                    </div>
                </div>
            </div>
        `
    });
})();
