(function() {
    randar.component('context-menu', {
        props: {
            active : Boolean,
            items  : Array
        },

        template: `
            <menu class="context" v-if="active" v-click-away="active = false">
                <menuitem v-for="item in items">
                    {{ item.text }}
                </menuitem>
            </menu>
        `
    });
})();
