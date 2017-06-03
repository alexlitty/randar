require('../init');
const async      = require('sync');
const decompress = require('decompress');
const mkdirp     = require('mkdirp');
const download   = require('../utility/download');
const tmp        = require('../utility/tmp');

if (fs.existsSync(path.join(RANDAR_PATH.LIB, 'libcef.so'))) {
    process.exit(0);
}

tmp.dir((error, tmpDir, tmpDone) => async.waterfall([
    (next) => {
        if (error) {
            next(error);
        } else {
            next();
        }
    },

    (next) => {
        const local  = path.join(tmpDir, 'cef.tar.bz2');
        const remote = 'http://opensource.spotify.com/cefbuilds/'
                     + 'cef_binary_3.3029.1619.geeeb5d7_linux64.tar.bz2';

        download(remote, local, (error) => {
            if (error) {
                next(error);
            } else {
                next(null, local);
            }
        });
    },

    (compressedFile, next) => {
        const extractionDir = path.join(path.dirname(compressedFile));

        decompress(compressedFile, extractionDir).then(() => {
            next(null, extractionDir);
        });
    },

    (extractionDir, next) => {
        
    }
], (err) => {
    let code = 0;
    if (err) {
        console.error(err.message);
        code = 1;
    } else {
        console.log('Installed CEF');
    }

    tmpDone();
    process.exit(code);
});
