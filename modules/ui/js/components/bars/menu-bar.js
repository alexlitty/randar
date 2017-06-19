ui.component('menu-bar', {
    data: function() {
        return {
            activeItem: null
        }
    },

    props: {
        text: String,
        items: Array,
        onClose: Function
    },

    methods: {
        onItemFocus: function(item) {
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

        onItemHover: function(item) {
            if (this.activeItem && item.contextMenu) {
                this.activeItem = item;
            }
        },

        onContextMenuClose: function(item) {
            if (this.activeItem === item) {
                this.activeItem = null;
            }
        }
    },

    template: `
        <menu class="bar drag-handle">
            <menuitem v-if="text">
                <div class="text">
                    {{ text }}
                </div>
            </menuitem>

            <menuitem v-for="item in items" :class="activeItem === item ? 'active' : ''">
                <div class="text"
                 @click="onItemFocus(item)"
                 @mouseover="onItemHover(item)">
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
