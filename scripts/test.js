var os    = require('os');
var path  = require('path');
var spawn = require('child_process').spawn;

var binDirectory = path.normalize(path.join(__dirname, '..', 'bin'));

var build = require('./build');
build(function(err) {
    if (err) {
        return;
    }

    var executable;
    if (process.platform === 'linux') {
        executable = 'randar';
    }

    else if (process.platform === 'win32') {
        executable = 'randar.exe';
    }

    else {
        console.error('Randar must be ran manually on', process.platform);
        return;
    }

    console.log('Running ' + executable + os.EOL);
    var randar = spawn(path.join(binDirectory, executable), [ ], {
        cwd: binDirectory
    });

    randar.stdout.on('data', function(data) {
        console.log(data.toString());
    });

    randar.stderr.on('data', function(data) {
        console.error(data.toString());
    });

    randar.on('error', function(error) {
        console.error(error);
    });
});
