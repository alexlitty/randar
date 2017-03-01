(function() {
    var randar = require('./randar');

    if ((window.location.search || '').indexOf('debug') > -1) {
        randar.debug = true;

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

                    objects: {
                        0: {
                            modelId: 0,
                            actions: [
                                {
                                    type     : "transform",
                                    frame    : 3,
                                    duration : 4,

                                    transform: {
                                        position: {
                                            x : 0.5,
                                            y : 0,
                                            z : 0
                                        },

                                        rotation: {
                                            axis: {
                                                x : 0,
                                                y : 1,
                                                z : 0
                                            },

                                            angle: 0.75
                                        }
                                    }
                                }
                            ]
                        }
                    }
                }
            }

        });

        window.addEventListener('load', function() {
            randar.ready();
        });
    }
})();
