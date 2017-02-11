if ((window.location.search || '').indexOf('debug') > -1) {
    window.setMonitorTarget = function(category, name) {
        console.info("Set monitor target to '" + category + "' #" + name);
    }

    window.getResources = function() {
        var data = {
            name: 'Test film',

            models: {
                0: "Test model 0",
                1: "Test model 1",
                2: "Test model 2"
            },

            textures: {
                0: "Test texture 0",
                1: "Test texture 1"
            }
        };

        return JSON.stringify(data);
    }

    window.addEventListener('load', function() {
        randar.ready();
    });
}
