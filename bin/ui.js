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
            if (isString(data[type])) {
                randar.resources[type] = data[type];
            }

            else {
                for (item in data[type]) {
                    randar.resources.textures[item] = data[type][item];
                }
            }
        }

        // Update project name.
        var projectInfo = getElement('#main .randar');
        if (randar.resources.name) {
            projectInfo.innerHTML = randar.resources.name;
        } else {
            projectInfo.innerHTML = 'Untitled Project';
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
        textures: { },
        shaders: { }
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

function isString(value) {
    return typeof value === 'string' || value instanceof String;
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
    hideElement(getElement('#settings'));
    showElement(getElement('#main'));
}

function showSettings() {
    hideElement(getElement('#main'));
    showElement(getElement('#settings'));
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
    randar.syncs.push({
        command: 'read'
    });
    showMain();

    var backButtons = getElements('nav ul.back');
    for (var i = 0; i < backButtons.length; i++) {
        backButtons[i].addEventListener('click', function() {
            showMain();
        });
    }

    var resourceItems = getElements('#main li');
    for (var i = 0; i < resourceItems.length; i++) {
        var item = resourceItems[i];
        var category = item.className;

        if (category == 'randar') {
            item.addEventListener('click', function() {
                showSettings();
            });
        }

        else {
            item.addEventListener('click', function(category) {
                showObjects(category);
            }.bind(this, category));
        }
    }
});
