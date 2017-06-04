(function() {
    Vue.directive('click-away', {
        bind: function(el, binding, vnode) {
            el.clickAwayFn = function(event) {
                if (!(el == event.target || el.contains(event.target))) {
                    vnode.context[binding.expression]();
                }
            }

            setTimeout(function() {
                document.body.addEventListener('click', el.clickAwayFn);
            }, 0);
        },

        unbind: function(el) {
            document.body.removeEventListener('click', el.clickAwayFn);
        }
    });
})();
