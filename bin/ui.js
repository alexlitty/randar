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
    showElement(getElement("#main"));
});
