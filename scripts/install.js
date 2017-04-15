const async = require('async');
const http  = require('http');
const spawn = require('child_process').spawn;

async.series([

    (next) => http.get({
        host     : 'superb-dca2.dl.sourceforge.net',
        path     : '/project/swig/swig/swig-3.0.12/swig-3.0.12.tar.gz'
    }, (result) => next(null, result)),

    (response, next) => {
        console.log(response)
        response.on('data', (data) => {
            console.log(data);
            response.on('end', next);
        });

        response.req.on('error', (error) => {
            console.error(error);
        });

        response.req.on('end', () => next);
    }

], (err) => {
    if (err) {
        console.error(err);
    }
});

//https://superb-dca2.dl.sourceforge.net
