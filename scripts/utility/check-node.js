const config = require('../../config');

function checkNode() {
    return process.version === config.requirements.node;
}

if (module.parent) {
    module.exports = checkNode;
} else {
    process.exit(checkNode() ? 0 : 1);
}
