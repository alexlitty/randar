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

        template: `
            <div id="main-menu-bar">
                <menu-bar :items="items"></menu-bar>
            </div>
        `
    });
})();
