if ((window.location.search || '').indexOf('debug') > -1) {
    window.setMonitorTarget = function(category, name) {
        if (_.isNull(name) || _.isNull(category)) {
            console.info("Set monitor target to nothing");
        }
        
        else {
            console.info("Set monitor target to '" + category + "' #" + name);
        }
    }

    window.importResource = function() {
        console.info("Resource would be imported");
    }

    randar.receiveData({
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
    });

    window.addEventListener('load', function() {
        randar.ready();
    });
}
