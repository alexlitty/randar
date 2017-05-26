const mkdirp = require('mkdirp');
const path   = require('path');

module.exports = (randar) => {
    randar.tmp = {
        dir  : '/tmp/randar',

        file : (filename) => {
            mkdirp.sync(randar.tmp.dir);
            return path.join(randar.tmp.dir, filename);
        }
    };
};
