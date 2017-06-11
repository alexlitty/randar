ui.component('project-folder', {
    props: {
        folder: Object
    },

    data: function() {
        return {
            enableNewMenu : false,
            newMenuGroups : [
                [
                    { text: 'Folder', action: function() {
                        this.project.newFolder('Untitled folder', this.folder.id);
                    }.bind(this)}
                ]
            ]
        }
    },

    computed: {
        test : function() {
            this.$forceUpdate();
            if (!this.project || !this.project.folders || !Object.keys(this.project.folders).length) {
                return 'Unknown';
            }
            return Object.keys(this.project.folders).length;
        }
    },

    methods: {
        onClickNew: function() {
            this.enableNewMenu = true;
        },

        onNewMenuClose: function() {
            this.enableNewMenu = false;
        }
    },

    template: `
        <div class="folder">
            <div class="data">
                {{ folder.name }}
            </div>

            <div class="new" @click="onClickNew">
                +

                <context-menu
                    v-if="enableNewMenu"
                    :groups="newMenuGroups"
                    @close="onNewMenuClose">
                </context-menu>
            </div>

            <div class="subfolders">
                <project-folder
                    v-for="subfolder in folder.folders"
                    :key="subfolder.id">
                </project-folder>
            </div>

            <div class="items">
            </div>
        </div>
    `
});
