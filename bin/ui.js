/**
 * Bridges interactions between the interface and the engine.
 *
 * Initialized by Randar.
 */
var randar = {
    test: function() {
        getElement("#main .randar").innerHTML = 'Test works!';
    }
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
