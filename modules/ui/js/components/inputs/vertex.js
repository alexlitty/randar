ui.component('input-vertex', {
    props: {
        value: Object,
    },

    methods: {
        onInputPosition: function(position) {
            this.value.position = position;
            this.$emit('input', this.value);
        }
    },

    template: `
        <div class="input vertex">
            <div class="position">
                Position
                <input-vector3
                 :value.sync="value.position"
                 @input="onInputPosition">
                </input-vector3>
            </div>
        </div>
    `
});
