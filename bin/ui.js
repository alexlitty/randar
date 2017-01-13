var randar = {
    /**
     * Engine sync requests.
     *
     * The engine looks at this array every frame and initiates a sync if
     * information is required.
     */
    syncs: [ ],

    /**
     * Retrieves and clears the engine sync requests.
     */
    consumeSyncs: function() {
        var syncs = randar.syncs.slice();
        randar.syncs = [ ];
        return syncs;
    },

    /**
     * Updates one or more resources.
     */
    updateResources: function(data) {
        for (type in data) {
            for (item in data[type]) {
                randar.resources.textures[item] = data[type][item];
            }
        }

        // Update list elements.
        var texturesList = getElement('#objects .textures');
        for (textureName in randar.resources.textures) {
            var element = document.createElement('li');
            element.innerHTML = textureName;
            texturesList.appendChild(element);
        }
    },


    /**
     * Project resources.
     */
    resources: {
        textures: { }
    }
};

/**
 * Generic helpers.
 */
function getElement(query) {
    return document.querySelector(query);
}

function getElements(query) {
    return document.querySelectorAll(query);
}

function hideElement(element) {
    element.classList.add('hidden');
}

function showElement(element) {
    element.classList.remove('hidden');
}


/**
 * Program-specific helpers.
 */
function showMain() {
    var objectLists = getElements('#objects ul');
    for (var i = 0; i < objectLists.length; i++) {
        var element = objectLists[i];

        if (element.className != 'back') {
            hideElement(element);
        }
    }

    hideElement(getElement('#objects'));
    showElement(getElement('#main'));
}

function showObjects(category) {
    hideElement(getElement('#main'));
    showElement(getElement('#objects'));

    showElement(getElement('#objects ul.' + category));
}


/**
 * Main program.
 */
window.addEventListener('load', function() {
    randar.syncs.push("everything");
    showElement(getElement('#main'));

    getElement('#objects ul.back').addEventListener('click', function() {
        showMain();
    });

    getElement('#main .textures').addEventListener('click', function() {
        showObjects('textures');
    });
});
