ui.component('input-color', {
    props: {
        value: Object,
    },

    computed: {
        previewColor: function() {
            return 'rgba(' + this.value.r +
                   ',' + this.value.g +
                   ',' + this.value.b +
                   ',' + (this.value.a / 255) + ')';
        }
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
            this.value.b = newB;
            this.$emit('input', this.value)
        },

        onUpdateA: function(newA) {
            this.value.a = newA;
            this.$emit('input', this.value)
        }
    },

    template: `
        <div class="input color">
            <div class="preview" :style="{ backgroundColor: previewColor }">&nbsp;</div>
            <input-text :value.sync="value.r" :label="'r'" @input="onUpdateR"></input-text>
            <input-text :value.sync="value.g" :label="'g'" @input="onUpdateG"></input-text>
            <input-text :value.sync="value.b" :label="'b'" @input="onUpdateB"></input-text>
            <input-text :value.sync="value.a" :label="'a'" @input="onUpdateA"></input-text>
        </div>
    `
});
