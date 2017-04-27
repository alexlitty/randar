const os       = require('os');
const path     = require('path');
const voidFile = os.platform() === 'win32' ? 'NUL' : '/dev/null';

/**
 * Register a segfault listener.
 *
 * This will display some hopefully-helpful information when a segfault occurs.
 * Which shouldn't happen, because our code is perfect, right? Right?!
 *
 * We specify /dev/null to 
 */
global.SegfaultHandler = require('segfault-handler');
SegfaultHandler.registerHandler(voidFile);

/**
 * Dummy Mocha function so this file is picked up while testing.
 */
before(() => {
});
