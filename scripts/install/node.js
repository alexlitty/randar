const spawn   = require('child_process').spawn;
const helpers = require('../helpers');

if (process.version === helpers.requirements.node) {
    console.log('Node.js is running at required version.');
    process.exit(0);
}

console.log(
    `Running Node.js ${process.version}. `
    + `Attempting to install required ${helpers.requirements.node}.`
);

try {
    const opt = { stdio: 'inherit' };

    const install = spawn('sudo', ['npm', 'install', '-g', 'n'], opt);
    console.log('Installing version manager "n"');

    install.on('close', (code) => {
        if (code !== 0) {
            throw new Error('Failed to install n.');
        }

        const use = spawn('sudo', ['n', helpers.requirements.node.slice(1)], opt);
        console.log(`Requiring Node.js ${helpers.requirements.node}`);

        use.on('close', (code) => {
            if (code !== 0) {
                throw new Error('Failed to install or switch Node.js version.');
            }
        });
    });
}

catch (e) {
    console.error(e.message, 'Manual installation may be required.');
    process.exit(1);
}
