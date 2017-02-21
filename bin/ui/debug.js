if ((window.location.search || '').indexOf('debug') > -1) {
    window.saveProject = function() {
        console.info("Project would be saved");
    }

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

    window.createResource = function(category) {
        console.info("New resource would be created in " + category);
    }

    window.setModelMeshTexture = function(modelId, slotId, textureId) {
        console.info("Model #" + modelId + ", texture slot #" + slotId + " would be set to texture #" + textureId);
    }

    randar.receiveData({
        name: 'Test film',

        textures: {
            0: {
                name: "Example texture",

                type: "rgba",
                width: 200,
                height: 140
            }
        },

        models: {
            0: {
                name: "Example model",

                vertexCount: 1016,
                faceCount: 2464,

                textures: [0, null, 0]
            }
        },

        scenes: {
            0: {
                name: "Example scene",

                models: {
                }
            }
        }

    });

    window.addEventListener('load', function() {
        randar.ready();
    });
}
