before(function() {
    global.assert  = require('assert');
    global.os      = require('os');
    global.path    = require('path');

    global.adapter = require(
        path.join(__dirname, '..', 'modules', 'adapter', 'build/Debug/adapter.node')
    );

    const voidFile = os.platform() === 'win32' ? 'NUL' : '/dev/null';

    /**
     * Register a segfault listener.
     *
     * This will display some hopefully-helpful information when a segfault occurs.
     * Which shouldn't happen, because our code is perfect, right? Right?!
     *
     * registerHandler needs to be called to start listening for segfaults, and
     * automatically logs the relevant information to the console. It takes a
     * required filename argument to store the same information in; We don't really
     * need to save the information, so we pass the platform's "void" file handle.
     */
    global.SegfaultHandler = require('segfault-handler');
    SegfaultHandler.registerHandler(voidFile);
});
