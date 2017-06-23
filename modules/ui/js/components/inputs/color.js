ui.component('input-color', {
    props: {
        value: Object,
    },

    computed: {
        previewColor: function() {
            return 'rgba(' + this.value.rInt +
                   ',' + this.value.gInt +
                   ',' + this.value.bInt +
                   ',' + (this.value.aInt / 255) + ')';
        }
    },

    methods: {
        onUpdateR: function(newR) {
            this.value.rInt = newR;
            this.$emit('input', this.value)
        },

        onUpdateG: function(newG) {
            this.value.gInt = newG;
            this.$emit('input', this.value)
        },

        onUpdateB: function(newB) {
            this.value.bInt = newB;
            this.$emit('input', this.value)
        },

        onUpdateA: function(newA) {
            this.value.aInt = newA;
            this.$emit('input', this.value)
        }
    },

    template: `
        <div class="input color">
            <div class="preview" :style="{ backgroundColor: previewColor }">&nbsp;</div>
            <input-text :value.sync="value.rInt" :label="'r'" @input="onUpdateR"></input-text>
            <input-text :value.sync="value.gInt" :label="'g'" @input="onUpdateG"></input-text>
            <input-text :value.sync="value.bInt" :label="'b'" @input="onUpdateB"></input-text>
            <input-text :value.sync="value.aInt" :label="'a'" @input="onUpdateA"></input-text>
        </div>
    `
});
