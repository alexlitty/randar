ui.component('project-folder', {
    props: {
        folderId: Object
    },

    data: function() {
        return {
            folder : ui.project.folders[folderId]
        }
    },

    template: `
        <div class="bin-folder">
            {{ folder.name }}

            <project-folder v-for="(subfolder, subfolderId) in folder.folders"></project-folder>
        </div>
    `
});
