(function() {
    Vue.filter('titlecase', function(value) {
        if (!_.isString(value) || !value.length) {
            return value;
        }

        return value.charAt(0).toUpperCase() + value.slice(1);
    });
})();
