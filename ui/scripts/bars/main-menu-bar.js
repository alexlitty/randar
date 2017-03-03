(function() {
    randar.component('main-menu-bar', {
        computed: {
            items: function() {
                return [
                    {
                        text: 'Randar',
                        active: true,
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
                    { text: 'Project' },
                    { text: 'Help'    }
                ];
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
