before(function() {
    /**
     * Global declarations that will be available in all tests, even when
     * exclusively run with Mocha's .only.
     */
    global.assert  = require('assert');
    global.os      = require('os');
    global.path    = require('path');

    global.voidFile = os.platform() === 'win32' ? 'NUL' : '/dev/null';
    global.randar = require('..');

    /**
     * Register a segfault listener.
     *
     * This will display some hopefully-helpful information when a segfault occurs.
     * Which shouldn't happen, because our code is perfect, right? Right?!
     *
     * registerHandler needs to be called to start listening for segfaults. Once
     * called, it automatically logs such events to the console. It takes a
     * required filename argument to store the same information in; We don't
     * really need to save the information, so we pass the platform's "void"
     * file handle.
     *
     * You can configure the adapter to build as a debug module, but it doesn't
     * seem to provide any additional information here. The release module
     * symbols appear descriptive enough for most problems anyway.
     */
    global.SegfaultHandler = require('segfault-handler');
    SegfaultHandler.registerHandler(voidFile);
});
