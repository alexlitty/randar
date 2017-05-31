/**
 * A button to navigate to the previous panel.
 */
ui.component('back-button', {
    props: {
        action: Function
    },

    template: `
        <ul class="back">
            <li v-on:click="action()">&larrhk;</li>
        </ul>
    `
});
