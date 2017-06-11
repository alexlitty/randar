ui.component('new-entity', {
    data: function() {
        return {
            type : ui.params.get('type'),
            name : ''
        }
    },

    methods: {
        onClose: function() {
            ui.exit();
        },

        onSubmit: function() {
            if (this.type === 'bin') {
                ui.project.newFolder(this.name, null);
            }

            ui.exit();
        }
    },

    template: `
        <div class="dialog">
            <menu-bar :onClose="onClose"></menu-bar>

            <div v-if="type === 'bin'">
                <input type="text" v-model="name">
                <input type="submit" value="*" @click="onSubmit">
            </div>
        </div>
    `
});
