global.config = require('./config');

// Commonly used node packages.
global.child_process = require('child_process');
global.spawn         = child_process.spawn;

global.fs       = require('fs');
global.http     = require('http');
global.https    = require('https');
global.os       = require('os');
global.path     = require('path');
global.url      = require('url');

// Absolute paths to different parts of the Randar project.
var p = { };
global.RANDAR_PATH = p;

p.ROOT           = path.join('..', '..');
p.MODULES        = path.join(p.ROOT, 'modules');
p.ENGINE         = path.join(p.MODULES, 'engine');
p.ENGINE_INCLUDE = path.join(p.ENGINE, 'include', 'randar');
p.ENGINE_SOURCE  = path.join(p.ENGINE, 'src');
p.ADAPTER        = path.join(p.MODULES, 'adapter');
p.UI             = path.join(p.MODULES, 'ui');

for (key in p) {
    p[key] = path.resolve(path.join(__dirname, p[key]));
}
