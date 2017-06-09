ui.component('project-bins', {
    data: function() {
        return {
            bins: ui.project.bins
        }
    },

    methods: {
        onClose: function() {
            ui.exit();
        }
    },

    template: `
        <div class="dialog bins">
            <menu-bar :onClose="onClose"></menu-bar>

            <div v-if="bins && bins.length">
                <project-folder v-for="(bin, binId) in bins" folderId="binId">
                </project-folder>
            </div>

            <div v-else class="empty">
                No bins available.
            </div>
        </div>
    `
});
