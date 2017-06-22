ui.component('input-text', {
    props: {
        value: { validator: () => true },
        label: { validator: () => true }
    },

    methods: {
        onInput: function(e) {
            this.$emit('input', e.target.value);
        }
    },

    template: `
        <div class="input text">
            <div v-if="label" class="label">
                {{ label }}
            </div>
            <input class="input text" type="text" :value.sync="value" @input="onInput">
        </div>
    `
});
