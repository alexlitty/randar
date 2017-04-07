randar.component('overlay', {
    props: {
        name: String
    },

    methods: {
        hideOverlay: function() {
            this.$set(this.overlays, this.name, false);
        }
    },

    template: `
        <div class="overlay" v-if="overlays[name]">
            <div class="content" v-click-away="hideOverlay">
                <slot></slot>
            </div>
        </div>
    `
});
