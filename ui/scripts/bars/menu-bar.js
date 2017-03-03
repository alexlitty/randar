(function() {
    randar.component('menu-bar', {
        data: function() {
            return {
                activeItem: null
            }
        },

        props: {
            items: Array,
            onClose: Function
        },

        methods: {
            onItemClick: function(item) {
                if (this.activeItem === item) {
                    this.activeItem = null;
                    return;
                }

                if (item.contextMenu) {
                    this.activeItem = item;
                }

                if (item.onClick) {
                    item.onClick();
                }
            },

            onContextMenuClose: function(item) {
                if (this.activeItem === item) {
                    this.activeItem = null;
                }
            }
        },

        template: `
            <menu class="bar">
                <menuitem v-for="item in items" :class="activeItem === item ? 'active' : ''">
                    <div class="text" @click="onItemClick(item)">
                        {{ item.text }}
                    </div>

                    <context-menu v-if="item.contextMenu && activeItem === item"
                     :groups="item.contextMenu"
                     @close="onContextMenuClose(item)">
                    </context-menu>
                </menuitem>

                <menuitem class="close" v-if="onClose" @click="onClose">

                </menuItem>
            </menu>
        `
    });
})();
