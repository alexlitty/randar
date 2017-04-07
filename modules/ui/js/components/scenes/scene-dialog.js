(function() {
    /**
     * A timeline for scene editing.
     */
    module.exports = randar.component('scene-dialog',
        {
            props: {
                scene: Object
            },

            data: function() {
                return {
                    selectedFrame: 0
                };
            },

            computed: {
                zoom: function() {
                    return 75;
                },

                width: function() {
                    return this.frames.length * this.zoom;
                },

                frames: function() {
                    var result = [];

                    for (var i = 0; i < 60; i++) {
                        result.push({
                            id: i,
                            significant: this.isFrameSignificant(i)
                        });
                    }

                    return result;
                }
            },

            methods: {
                isFrameSignificant: function(id) {
                    return id % 5 === 0;
                },

                onGuideFrameSelected: function(frameId) {
                    this.selectedFrame = frameId;
                }
            },

            template: `
                <dialog-box class="scene-dialog" v-if="scene">
                    <div class="guide" :style="{ width: width }">
                        <header class="drag-handle">Objects</header>

                        <div class="markers drag-handle">
                            <timeline-marker
                             v-for="frame in frames" :key="frame.id"
                             :markerId="frame.id"
                             :zoom="zoom"
                             :frame="frame.id"
                             :duration="1"
                             :significant="frame.significant"
                             :selected="selectedFrame === frame.id"
                             @markerSelected="onGuideFrameSelected">
                                <span v-if="frame.significant">{{ frame.id }}</span>
                            </timeline-marker>
                        </div>
                    </div>

                    <div class="items" :style="{ width: width }">
                        <div class="item" v-for="(object, objectId) in scene.objects">
                            <header>{{ objectId }}</header>

                            <div class="markers">
                                <timeline-marker
                                 v-for="(action, actionId) in object.actions" :key="actionId"
                                 :markerId="actionId"
                                 :zoom="zoom"
                                 :frame="action.frame"
                                 :duration="action.duration">
                                    Transform
                                </timeline-marker>
                            </div>
                        </div>
                    </div>
                </dialog-box>
            `
        }
    );
})();
