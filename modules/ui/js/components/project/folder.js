ui.component('project-folder', {
    props: {
        folderId: Object
    },

    data: function() {
        return {
            folders : ui.project.folders[folderId].folderIds,
            items   : ui.project.folders[folderId].itemIds
        }
    },

    template: `
        <div class="bin-folder">
            <project-folder v-for="item in items"></project-folder>
        </div>
    `
});
