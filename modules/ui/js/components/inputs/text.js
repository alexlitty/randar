ui.component('input-text', {
    props: {
        value: { validator: () => true }
    },

    methods: {
        onInput: function(e) {
            this.$emit('input', e.target.value);
        }
    },

    template: `
        <input class="input text" type="text" :value.sync="value" @input="onInput">
    `
});
