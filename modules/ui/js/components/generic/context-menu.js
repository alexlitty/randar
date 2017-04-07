randar.component('context-menu', {
    props: {
        groups : Array
    },

    methods: {
        onClose: function() {
            this.$emit('close');
        },

        onItemClick: function(item) {
            this.$emit('close');

            if (item.action) {
                item.action();
            }
        }
    },

    template: `
        <menu class="context" v-click-away="onClose">
            <menu class="group" v-for="group in groups">
                <menuitem v-for="item in group" @click="onItemClick(item)">
                    {{ item.text }}
                </menuitem>
            </menu>
        </menu>
    `
});
