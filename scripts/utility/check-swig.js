const spawn  = require('child_process').spawn;
const config = require('../../config');

function checkSwig(cb) {
    const swig = spawn('swig', ['-v'], { stdio: 'ignore' });

    let version = '';
    swig.on('data', (data) => {
        version += data.toString();
    });

    swig.on('error', () => {});
    swig.on('close', (code) => {
        cb(code === 0 && version === config.requirements.swig);
    });
}

if (module.parent) {
    module.exports = checkSwig;
} else {
    checkSwig((good) => process.exit(good ? 0 : 1));
}
