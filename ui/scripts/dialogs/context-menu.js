(function() {
    randar.component('context-menu', {
        props: {
            groups : Array
        },

        methods: {
            onClose: function() {
                this.$emit('close');
            }
        },

        template: `
            <menu class="context" v-click-away="onClose">
                <menu class="group" v-for="group in groups">
                    <menuitem v-for="item in group">
                        {{ item.text }}
                    </menuitem>
                </menu>
            </menu>
        `
    });
})();
