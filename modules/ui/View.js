/**
 * A view in the UI.
 *
 * Each view is composed of browsers and preview windows. Browsers allow user
 * interaction, preview windows provide engine renderings.
 */
randar.ui.View = function(type) {
    this.type = type;

    this.browsers = [];
    this.previews = [];

    if (this.type === 'main') {
        this.browsers.push('main');
        this.browsers.push('bins');
    }

    else if (this.type === 'about') {
        this.browsers.push('about');
    }

    else {
        console.warn('Creating unknown View type:', type);
    }

    this.browsers = this.browsers.map((browserType) => {
        return new randar.ui.Browser(browserType);
    });
}

/**
 * Requests a view to be closed.
 */
randar.ui.View.prototype.close = function() {
    this.browsers.forEach((browser) => browser.close());
}
