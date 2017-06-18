ui.component('project-item', {
    props: {
        item: Object
    },

    methods: {
        onMonitor: function() {
            ui.monitor(this.item);
        }
    },

    template: `
        <div class="item">
            <div class="data" :class="item.kind" @click="onMonitor">
                {{ item.name }}
            </div>
        </div>
    `
});
