ui.component('input-vertex', {
    props: {
        value: Object,
    },

    methods: {
        onInputPosition: function(position) {
            this.value.position = position;
            this.$emit('input', this.value);
        },

        onInputColor: function(color) {
            this.value.color = color;
            this.$emit('input', this.value);
        }
    },

    template: `
        <div class="input vertex">
            <table>
                <tr>
                    <td>Position</td>
                    <td>
                        <input-vector3
                         :value.sync="value.position"
                         @input="onInputPosition">
                        </input-vector3>
                    </td>
                </tr>

                <tr>
                    <td>Color</td>
                    <td>
                        <input-color
                         :value.sync="value.color"
                         @input="onInputColor">
                        </input-color>
                    </td>
                </tr>
            </table>
        </div>
    `
});
