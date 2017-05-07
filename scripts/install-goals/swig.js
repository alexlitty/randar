const async = require('async');
const https = require('https');
const path  = require('path');
const spawn = require('child_process').spawn;
const targz = require('targz');

const config   = require('../../config');
const download = require('../utility/download');
const tmp      = require('../utility/tmp');

tmp.dir((error, tmpDir, tmpDone) => async.waterfall([
    (next) => {
        if (error) {
            next(error);
        } else {
            next();
        }
    },

    (next) => {
        const local  = path.join(tmpDir, 'swig.tar.gz');
        const remote = 'https://github.com/swig/swig/archive/'
                     + `rel-${config.requirements.swig}.tar.gz`;

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

        targz.decompress({
            src  : compressedFile,
            dest : extractionDir,
        }, (error) => {
            if (error) {
                next(error);
            } else {
                next(null, path.join(
                    extractionDir, `swig-rel-${config.requirements.swig}`
                ));
            }
        });
    },

    (swigDir, next) => {
        const autogen = spawn('./autogen.sh', [], {
            cwd   : swigDir,
            stdio : 'inherit'
        });

        autogen.on('close', (code) => {
            if (code !== 0) {
                next(new Error('Failed to pre-configure SWIG for compilation'));
            } else {
                next(null, swigDir);
            }
        });
    },

    (swigDir, next) => {
        const configure = spawn('sh', [path.join(swigDir, 'configure')], {
            cwd   : swigDir,
            stdio : 'inherit'
        });

        configure.on('close', (code) => {
            if (code !== 0) {
                next(new Error('Failed to configure SWIG for compilation'));
            } else {
                next(null, swigDir);
            }
        });
    },

    (swigDir, next) => {
        const make = spawn('make', ['-C', swigDir], {
            cwd   : swigDir,
            stdio : 'inherit'
        });

        make.on('close', (code) => {
            if (code !== 0) {
                next(new Error('Failed to compile SWIG'));
            } else {
                next(null, swigDir);
            }
        });
    },

    (swigDir, next) => {
        const install = spawn('sudo', ['make', 'install', '-C', swigDir], {
            cwd   : swigDir,
            stdio : 'inherit'
        });

        install.on('close', (code) => {
            if (code !== 0) {
                next(new Error('Failed to install SWIG'));
            } else {
                next();
            }
        });
    }

], (err) => {
    let code = 0;
    if (err) {
        console.error(err.message);
        code = 1;
    } else {
        console.log(`Installed SWIG ${config.requirements.swig}`);
    }

    tmpDone();
    process.exit(code);
}));
