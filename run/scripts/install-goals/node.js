require('../init');
const checkNode = require('../utility/check-node');

if (checkNode()) {
    process.exit(0);
}

console.log(
    `Detected node.js ${process.version}. `
    + `Attempting to install required ${config.requirements.node}.`
);

try {
    const opt = { stdio: 'inherit' };

    const install = spawn('sudo', ['npm', 'install', '-g', 'n'], opt);
    install.on('close', (code) => {
        if (code !== 0) {
            throw new Error('Failed to install n.');
        }

        const use = spawn('sudo', ['n', config.requirements.node.slice(1)], opt);
        use.on('close', (code) => {
            if (code !== 0) {
                throw new Error('Failed to install or switch Node.js version.');
            }

            console.log(`Node.js ${config.requirements.node} installed.`);
        });
    });
}

catch (e) {
    console.error(e.message, 'Manual installation may be required.');
    process.exit(1);
}
