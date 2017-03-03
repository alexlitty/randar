(function() {
    randar.component('menu-bar', {
        props: {
            items: Array,
            onClose: Function
        },

        methods: {
            onItemClick: function(item) {
                if (item.contextMenu) {
                    item.active = true;
                }

                if (item.onClick) {
                    item.onClick();
                }
            }
        },

        template: `
            <menu class="bar">
                <menuitem v-for="item in items" @click="onItemClick(item)">
                    {{ item.text }}

                    <context-menu v-if="item.contextMenu && item.active"
                     v-click-away="item.active = false"
                     :groups="item.contextMenu">
                    </context-menu>
                </menuitem>

                <menuitem class="close" v-if="onClose" @click="onClose">

                </menuItem>
            </menu>
        `
    });
})();
