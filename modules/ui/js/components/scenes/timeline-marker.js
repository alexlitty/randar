/**
 * A marker on a timeline.
 *
 * Indicates an action. Also used to create the timeline headers.
 */
randar.component('timeline-marker', {
    props: {
        markerId    : Number,
        zoom        : Number,
        frame       : Number,
        duration    : Number,
        significant : Boolean,
        selected    : Boolean
    },

    computed: {
        classes: function() {
            var result = ['marker'];

            if (this.significant) {
                result.push('significant');
            }

            if (this.selected) {
                result.push('selected');
            }

            return result;
        },

        style: function() {
            var width = (this.zoom * this.duration) - 1;
            if (width <= 0) {
                width = 1;
            }

            return {
                left  : this.zoom * this.frame,
                width : width
            };
        }
    },

    methods: {
        onClick: function() {
            this.$emit('markerSelected', this.markerId);
        }
    },

    template: `
        <div :class="classes" :style="style" @click="onClick">
            <div>
                <slot></slot>
            </div>
        </div>
    `
});
