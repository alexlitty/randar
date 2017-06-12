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
                        this.project.newFolder('Untitled folder', this.folder);
                    }.bind(this)}
                ],

                [
                    { text: 'Geometry', action: function() {
                        this.project.newItem(
                            this.folder,
                            'geometry',
                            'Untitled geometry'
                        );
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
            this.$forceUpdate();
        }
    },

    template: `
        <div class="folder">
            <div class="data">
                {{ folder.name }}

                <div class="new" @click="onClickNew">
                    +
                </div>
            </div>

            <div class="contents">
                <project-folder
                    v-for="subfolder in folder.folders"
                    :key="subfolder.id"
                    :folder="subfolder">
                </project-folder>

                <project-item
                    v-for="item in folder.items"
                    :key="item.id"
                    :item="item">
                </project-item>
            </div>

            <context-menu
                v-if="enableNewMenu"
                :groups="newMenuGroups"
                @close="onNewMenuClose">
            </context-menu>

        </div>
    `
});
