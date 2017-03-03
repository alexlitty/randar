(function() {
    randar.component('main-menu-bar', {
        data: function () {
            return {
                items: [
                    {
                        text: 'Randar',
                        active: null,
                        contextMenu: [
                            [
                                { text: 'New Project' },
                                { text: 'Open Project' }
                            ],

                            [
                                { text: 'Close' }
                            ]
                        ]
                    },
                    {
                        text: 'Help',
                        contextMenu: [
                            [
                                { text: 'About' }
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
