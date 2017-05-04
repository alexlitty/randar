const spawn   = require('child_process').spawn;
const helpers = require('./helpers');

if (process.version !== helpers.requirements.node) {
    throw new Error(
        `Node ${helpers.requirements.node} required. `
        + `Current is ${process.version}. Try:`
        + '\n\n'
        + 'sudo npm install -g n\n'
        + 'sudo n 6.10.3'
    );
}
