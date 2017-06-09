ui.component('project-bins', {
    methods: {
        onClose: function() {
            ui.exit();
        }
    },

    template: `
        <menu-bar :onClose="onClose"></menu-bar>
    `
});
