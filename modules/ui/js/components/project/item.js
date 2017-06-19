ui.component('project-item', {
    props: {
        item: Object
    },

    methods: {
        onClick: function() {
            ui.monitor(this.item);
            this.$set(this.itemDialogs, this.item.id, this.item);
        }
    },

    template: `
        <div class="item">
            <div class="data" :class="item.kind" @click="onClick">
                {{ item.name }}
            </div>
        </div>
    `
});
