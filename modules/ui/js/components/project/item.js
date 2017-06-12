ui.component('project-item', {
    props: {
        item: Object
    },

    template: `
        <div class="item">
            <div class="data" :class="item.kind">
                {{ item.name }}
            </div>
        </div>
    `
});
