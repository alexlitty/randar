ui.component('input-color', {
    props: {
        value: Object,
    },

    methods: {
        onUpdateR: function(newR) {
            this.value.r = newR;
            this.$emit('input', this.value)
        },

        onUpdateG: function(newG) {
            this.value.g = newG;
            this.$emit('input', this.value)
        },

        onUpdateB: function(newB) {
            this.value.b = newR;
            this.$emit('input', this.value)
        },

        onUpdateA: function(newA) {
            this.value.a = newA;
            this.$emit('input', this.value)
        }
    },

    template: `
        <div class="input color">
            <input-text :value.sync="value.r" @input="onUpdateR"></input-text>
            <input-text :value.sync="value.g" @input="onUpdateG"></input-text>
            <input-text :value.sync="value.b" @input="onUpdateB"></input-text>
            <input-text :value.sync="value.a" @input="onUpdateA"></input-text>
        </div>
    `
});
