randar.component('main-menu-bar', {
    data: function() {
        return {
            items: [
                {
                    text: 'Randar',
                    contextMenu: [
                        [
                            { text: 'Save Project', action: function() {
                                randar.engine.saveProject();
                            }}
                        ],

                        [
                            { text: 'New Project'  },
                            { text: 'Open Project' }
                        ],

                        [
                            { text: 'Toggle DevTools', action: function() {
                                randar.browser.toggleDevTools();
                            }}
                        ],

                        [
                            { text: 'Close', action: function() {
                                randar.exit();
                            }}
                        ]
                    ]
                },

                {
                    text: 'Project',
                    contextMenu: [
                        [
                            { text: 'Create scene', action: function() {
                                window.createResource('scenes');
                            }}
                        ],

                        [
                            { text: 'Import resource', action: function() {
                                randar.importResource();
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
            randar.exit();
        }
    },

    template: `
        <div id="main-menu-bar">
            <menu-bar :items="items" :onClose="onClose"></menu-bar>
        </div>
    `
});
