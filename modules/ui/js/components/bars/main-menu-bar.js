ui.component('main-menu-bar', {
    data: function() {
        return {
            items: [
                {
                    text: 'Randar',
                    contextMenu: [
                        [
                            { text: 'Save Project', action: function() {
                                ui.engine.saveProject();
                            }}
                        ],

                        [
                            { text: 'New Project'  },
                            { text: 'Open Project' }
                        ],

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
                    text: 'Project',
                    contextMenu: [
                        [
                            { text: 'Create scene', action: function() {
                                ui.engine.createResource('scenes');
                            }}
                        ],

                        [
                            { text: 'Import resource', action: function() {
                                ui.importResource();
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
            this.$set(this.overlays, 'about', true);
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
