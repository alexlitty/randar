randar.component('main-menu-bar', {
    data: function () {
        return {
            items: [
                {
                    text: 'Randar',
                    contextMenu: [
                        [
                            { text: 'Save Project', action: function() {
                                window.saveProject();
                            }}
                        ],

                        [
                            { text: 'New Project'  },
                            { text: 'Open Project' }
                        ],

                        [
                            { text: 'Close', action: function() {
                                window.closeRandar();
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
                                window.importResource();
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
            window.closeRandar();
        }
    },

    template: `
        <div id="main-menu-bar">
            <menu-bar :items="items" :onClose="onClose"></menu-bar>
        </div>
    `
});
