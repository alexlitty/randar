(function() {
    randar.component('main-menu-bar', {
        data: function () {
            return {
                items: [
                    {
                        text: 'Randar',
                        contextMenu: [
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
                                { text: 'About Randar' }
                            ]
                        ]
                    }
                ]
            }
        },

        methods: {
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
})();
