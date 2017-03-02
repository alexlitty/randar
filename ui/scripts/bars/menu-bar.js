(function() {
    randar.component('menu-bar', {
        props: {
            items: Array
        },

        template: `
            <menu class="bar">
                <menuitem v-for="item in items">
                    {{ item.text }}
                </menuitem>
            </menu>
        `
    });
})();
