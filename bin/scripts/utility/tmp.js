require('../init');

function dir(routine) {
    const mktemp = spawn('mktemp', ['-d'], { stdio: 'pipe' });

    let tmpDir = '';
    mktemp.stdout.on('data', (data) => {
        tmpDir += data.toString().trim();
    });

    mktemp.on('error', () => {});

    mktemp.on('close', (code) => {
        if (code !== 0) {
            routine(new Error('Failed to create temporary directory'));
        } else {
            routine(null, tmpDir, () => {
                fs.rmdir(tmpDir, () => {});
            });
        }
    });
}

module.exports = { dir: dir }
