const async = require('async');
const https = require('https');
const path  = require('path');
const spawn = require('child_process').spawn;

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

    (response, next) => {
        /*response.on('data', (data) => {
            console.log(data);
            response.on('end', next);
        });

        response.req.on('error', (error) => {
            console.error(error);
        });

        response.req.on('end', () => next);*/
    }

], (err) => {
    let code = 0;
    if (err) {
        console.error(err.message);
        code = 1;
    }

    tmpDone();
    process.exit(code);
}));
