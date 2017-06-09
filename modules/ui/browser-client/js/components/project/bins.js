ui.component('project-bins', {
    data: function() {
        return {
            menuItems: [
                {
                    text: 'Bins',
                    contextMenu: [
                        [
                            { text: 'New bin', action: function() {
                                ui.emit('view.open', { type: 'new-bin' });
                            }}
                        ]
                    ]
                }
            ],

            bins: ui.project.bins
        }
    },

    methods: {
        onClose: function() {
            ui.exit();
        },

        createBin: function() {
        }
    },

    template: `
        <div class="dialog bins">
            <menu-bar :items="menuItems" :onClose="onClose"></menu-bar>

            <div v-if="bins && bins.length">
                <project-folder v-for="(bin, binId) in bins" :folderId="binId">
                </project-folder>
            </div>

            <div v-else class="empty">
                No bins available.
            </div>
        </div>
    `
});
