(function() {
    randar.component('overlay', {
        template: `
            <div class="overlay">
                <div class="content">
                    <slot></slot>
                </div>
            </div>
        `
    });
})();
