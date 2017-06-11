ui.component('project-folder', {
    props: {
        folder: Object
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

    template: `
        <div class="bin-folder">
            {{ folder.name }}

            <project-folder
                v-for="subfolder in folder.folders"
                :key="subfolder.id">
            </project-folder>
        </div>
    `
});
