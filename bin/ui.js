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

/** Program **/
var modes = {
    splash: function() {
        setTimeout(function() {
            switchMode('debug');
        }, 1000);
    },

    debug: function() {

    }
};

function switchMode(newMode) {
    var e;

    for (mode in modes) {
        e = getElement('section#' + mode);

        if (mode === newMode) {
            showElement(e);
        } else {
            hideElement(e);
        }
    }

    modes[newMode]();
};

window.addEventListener('load', function() {
    switchMode('splash');
});
