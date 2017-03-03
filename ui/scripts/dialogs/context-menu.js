(function() {
    randar.component('context-menu', {
        props: {
            groups : Array
        },

        template: `
            <menu class="context">
                <menu class="group" v-for="group in groups">
                    <menuitem v-for="item in group">
                        {{ item.text }}
                    </menuitem>
                </menu>
            </menu>
        `
    });
})();
