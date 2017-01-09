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
                textures[item] = data[type][item];
            }
        }
    },

    /**
     * Project resources.
     */
    textures: { }
};

/**
 * Helper functions.
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
 * Main program.
 */
window.addEventListener('load', function() {
    randar.syncs.push("textures");
    showElement(getElement('#main'));

    getElement('#objects ul.back').addEventListener('click', function() {
        hideElement(getElement('#objects'));
        showElement(getElement('#main'));

        getElement('#objects ul.list').className = 'list';
    });

    getElement('#main .textures').addEventListener('click', function() {
        hideElement(getElement('#main'));
        showElement(getElement('#objects'));

        getElement('#objects ul.list').classList.add(this.className);
    });
});
