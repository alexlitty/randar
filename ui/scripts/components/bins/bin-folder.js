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
            onItemClick: function(item) {
                if (!this.randar.resourcesWithDialogs.includes(item)) {
                    this.randar.resourcesWithDialogs.push(item);
                }
            }
        },

        template: `
            <div class="folder">
                <div v-if="!root"
                 :class="['name', expanded ? 'expanded' : null]"
                 @click="expanded = !expanded">
                    {{ folder.name }}
                </div>

                <div class="contents" v-if="expanded">
                    <bin-folder v-for="(subfolder, subfolderId) in folder.folders"
                     :key="subfolderId"
                     :folder="subfolder">
                    </bin-folder>

                    <div class="item" v-for="(item, itemId) in folder.items"
                     :key="itemId">
                        <div class="name" :class="item.resourceType"
                         @click="onItemClick(item)">
                            {{ item.name }}
                        </div>
                    </div>
                </div>
            </div>
        `
    });
})();
