ui.component('input-vector3', {
    props: {
        value: Object
    },

    methods: {
        onUpdateX: function(newX) {
            this.value.x = newX;
            this.$emit('input', this.value);
        },

        onUpdateY: function(newY) {
            this.value.y = newY;
            this.$emit('input', this.value);
        },

        onUpdateZ: function(newZ) {
            this.value.z = newZ;
            this.$emit('input', this.value);
        }
    },

    template: `
        <div class="input vector3">
            <input-text :value.sync="value.x" @input="onUpdateX"></input-text>
            <input-text :value.sync="value.y" @input="onUpdateY"></input-text>
            <input-text :value.sync="value.z" @input="onUpdateZ"></input-text>
        </div>
    `
});
