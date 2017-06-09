ui.component('main-menu-bar', {
    data: function() {
        return {
            items: [
                {
                    text: 'Randar',
                    contextMenu: [
                        /*[
                            { text: 'Save Project', action: function() {
                                if (ui.project.directory().toString() !== '.') {
                                    ui.project.save();
                                }
                            }}
                        ],

                        [
                            { text: 'New Project'  },
                            { text: 'Open Project' }
                        ],*/

                        [
                            { text: 'Toggle DevTools', action: function() {
                                ui.browser.toggleDevTools();
                            }}
                        ],

                        [
                            { text: 'Close', action: function() {
                                ui.exit();
                            }}
                        ]
                    ]
                },

                {
                    text: 'Help',
                    contextMenu: [
                        [
                            { text: 'About Randar', action: this.showAbout }
                        ]
                    ]
                }
            ]
        }
    },

    methods: {
        showAbout: function() {
            ui.emit('view.open', { type: 'about' });
        },

        onClose: function() {
            ui.exit();
        }
    },

    template: `
        <div id="main-menu-bar">
            <menu-bar :items="items" :onClose="onClose"></menu-bar>
        </div>
    `
});
