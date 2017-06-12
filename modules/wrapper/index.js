const randar = require('../adapter');

require('./Project/Project.js')(randar);
require('./Monitor.js')(randar);

module.exports = randar;
