ui.component('overlay-welcome', {
    data: function() {
        return {
            startingNewProject: false,
            projectName: 'Untitled Project'
        }
    },

    methods: {
        onNew: function() {
            this.startingNewProject = true;
        },

        onNewSubmit: function() {
            ui.project.name = this.projectName;
            ui.saveProject();
        },

        onLoad: function() {
            ui.loadProject();
        }
    },

    template: `
        <div class="overlay welcome">
            <div class="contents">
                <div class="logo">
                    Litty Studios
                    <header>RANDAR</header>
                </div>

                <div v-if="!startingNewProject">
                    <div class="button" @click="onNew">New Project</div>
                    <div class="button" @click="onLoad">Load Project</div>
                </div>

                <div v-else>
                    <input type="text" v-model="projectName">
                    <div class="button" @click="onNewSubmit">Create</div>
                </div>
            </div>
        </div>
    `
});
