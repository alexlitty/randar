/**
 * A list of resources in a particular category.
 */
ui.component('resource-list', {
    props: {
        category: String
    },

    methods: {
        onSelect: function(resourceId) {
            this.$emit('select', this.category, resourceId);
        }
    },

    template: `
        <ul class="resource-list">
            <li :class="category" v-for="(resource, resourceId) in resources[category]" v-on:click="onSelect(resourceId)">
                {{ resourceId }}
            </li>
        </ul>
    `
});
