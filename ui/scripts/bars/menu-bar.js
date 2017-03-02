(function() {
    randar.component('menu-bar', {
        props: {
            items: Array,
            onClose: Function
        },

        template: `
            <menu class="bar">
                <menuitem v-for="item in items">
                    {{ item.text }}
                </menuitem>

                <menuitem class="close" v-if="onClose" @click="onClose">

                </menuItem>
            </menu>
        `
    });
})();
