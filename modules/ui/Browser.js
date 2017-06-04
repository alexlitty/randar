/**
 * Representation of a browser instance.
 *
 * Requests a new browser be opened.
 */
randar.ui.Browser = function(type) {
    this.type = type;

    this.id = 0;
    while (randar.ui.Browser.list[this.id]) {
        this.id++;
    }

    randar.ui.clients.browsers.send({
        e    : 'browser.open',
        id   : this.id,
        type : this.type
    });
}

/**
 * Global list of browsers.
 */
randar.ui.Browser.list = { };

/**
 * Requests a browser to be closed.
 */
randar.ui.Browser.prototype.close = function() {
    randar.ui.clients.browsers.send({
        e  : 'browser.close',
        id : this.id
    });
}