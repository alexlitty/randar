(function() {
    var component = require('./component');

    /**
     * A overview panel for a resource category.
     */
    module.exports = component('resource-category-panel',
        {
            props: {
                category: String
            },

            methods: {
                onClose: function() {
                    this.target.resource.category = null;
                },

                onResourceSelect: function(category, resourceId) {
                    this.target.resource.category = category;
                    this.target.resource.id = resourceId;
                },

                create: function() {
                    window.createResource(this.category);
                }
            },

            template: `
                <div>
                    <nav id="resource-category" :class="category">
                        <back-button :action="onClose" />

                        <div class="options">
                            <div :class=category>
                                <div v-if="category === 'scenes'">
                                    <div class="button" @click="create">+ Create new scene</div>
                                </div>
                            </div>
                        </div>

                        <resource-list :category="category" @select="onResourceSelect" />
                    </nav>

                    <section class="info">
                        Select a resource.
                    </section>
                </div>
            `
        }
    );
})();
