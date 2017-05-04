const spawn = require('child_process').spawn;

let helpers = {
    requirements: {
        node: 'v6.10.3'
    }
};

/**
 * Creates a temporary directory.
 *
 * Callback is invoked with:
 *
 * err    : An Error if the directory could not be created, null otherwise
 * tmpDir : Full path to the temporary directory, if successfully created
 */
helpers.createTmpDir = (cb) => {
    const mktemp = spawn('mktemp', ['-d'], {
        stdio: ['pipe', 'pipe', process.stderr]
    });

    let tmpDir = '';
    mktemp.on('data', (data) => {
        tmpDir += data.toString();
    });

    mktemp.on('close', (code) => {
        if (code !== 0) {
            cb(new Error('Failed to create temporary directory'));
        } else {
            cb(null, tmpDir);
        }
    });
}

module.exports = helpers;
