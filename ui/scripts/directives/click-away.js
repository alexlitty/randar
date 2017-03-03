(function() {
    Vue.directive('click-away', {
        bind: function(el, binding, vnode) {
            this.event = function(event) {
                if (!(el == event.target || el.contains(event.target))) {
                    vnode.context[binding.expression](event);
                }
            }
        },

        unbind: function(el) {
            document.body.removeEventListener('click', this.event);
        }
    });
})();
