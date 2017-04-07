/**
 * An input to select a resource.
 */
randar.component('input-resource', {
    props: {
        category: String
    },

    methods: {
        onClose: function() {
            this.$emit('close');
        },

        onSelect: function(category, resourceId) {
            this.$emit('select', category, resourceId);
        }
    },

    template: `
        <nav id="resource-input">
            <back-button v-bind:action="onClose" />

            <resource-list :category="category" @select="onSelect" />
        </nav>
    `
});
