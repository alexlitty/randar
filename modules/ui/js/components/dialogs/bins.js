ui.component('project-bins', {
    data: function() {
        return {
            menuItems: [
                {
                    text: 'Bins',
                    contextMenu: [
                        [
                            { text: 'New bin', action: function() {
                                this.project.newFolder('Untitled bin', null);
                                this.$forceUpdate();
                            }.bind(this)}
                        ]
                    ]
                }
            ]
        }
    },

    methods: {
        onClose: function() {
            ui.exit();
        }
    },

    template: `
        <div class="dialog bins">
            <menu-bar :items="menuItems" :onClose="onClose"></menu-bar>

            <div v-if="project.hasBins()">
                <project-folder
                    v-for="bin in project.bins"
                    :key="bin.id"
                    :folder="bin">
                </project-folder>
            </div>

            <div v-else class="empty">
                No bins available.
            </div>
        </div>
    `
});
