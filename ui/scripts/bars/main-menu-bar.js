(function() {
    randar.component('main-menu-bar', {
        computed: {
            items: function() {
                return [
                    { text: 'Randar'  },
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
