(function() {
    randar.component('bin-folder', {
        props: {
            root     : Boolean,
            contents : Object
        },

        template: `
            <div class="folder">
                <div class="name" v-if="!root">{{ contents.name }}</div>

                <bin-folder v-for="(folder, folderId) in contents.folders"
                 :key="folderId"
                 :contents="folder">
                </bin-folder>

                <div class="item" v-for="(item, itemId) in contents.items"
                 :key="itemId">
                    <div class="name">{{ item.name }}</div>
                </div>
            </div>
        `
    });
})();
