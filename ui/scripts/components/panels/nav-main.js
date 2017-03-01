(function() {
    /**
     * The main panel.
     */
    module.exports = randar.component('nav-main',
        {
            template: `
                <div v-show="isNothingSelected()">
                    <nav id="main" v-show="isNothingSelected()">
                        <ul>
                            <li class="randar" v-on:click="selectSettings()">
                                {{ project.name }}
                            </li>

                            <li v-for="category in ['scenes', 'models', 'textures', 'shaders']"
                                v-bind:class="category" v-on:click="target.resource.category = category">
                                {{ category | titlecase }}
                            </li>
                        </ul>
                    </nav>

                    <section class="info">
                        Welcome to Randar.
                    </section>
                </div>
            `
        }
    );
})();
