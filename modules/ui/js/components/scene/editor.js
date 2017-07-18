ui.component('scene-editor', {
    props: {
        scene: Object
    },

    computed: {
        geometryActions: function() {
            let result = {};
        }
    },

    methods: {
        getFrameWidth: function() {
            return '10';
        },

        getActionWidth: function(action) {
            return action.frameCount * this.getFrameWidth();
        }
    },

    template: `
        <div class="scene-editor">
            <div v-for="action in scene.action"
        </div>
    `
});
