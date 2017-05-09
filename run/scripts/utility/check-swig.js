require('../init');

function checkSwig(cb) {
    const swig = spawn('swig', ['-version'], { stdio: 'pipe' });

    let output = '';
    swig.stdout.on('data', (data) => {
        output += data.toString();
    });

    swig.on('error', () => {});
    swig.on('close', (code) => {
        const re = new RegExp(
            `^SWIG Version ${config.requirements.swig.replace('.', '\\.')}$`,
            'm'
        );

        cb(code === 0 && re.test(output));
    });
}

if (module.parent) {
    module.exports = checkSwig;
} else {
    checkSwig((good) => process.exit(good ? 0 : 1));
}
