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

function clearElement(element) {
    element.innerHTML = '';
}

function toTitleCase(value) {
    if (!_.isString(value) || !value.length) {
        return value;
    }

    return value.charAt(0).toUpperCase() + value.slice(1);
}
