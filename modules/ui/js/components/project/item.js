ui.component('project-item', {
    props: {
        item: Object
    },

    template: `
        <div class="item">
            <div class="data" :class="item.type">
                {{ item.name }}
            </div>
        </div>
    `
});
