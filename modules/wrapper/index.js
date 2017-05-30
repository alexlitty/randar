const randar = require('../adapter');

require('./tmp')(randar);
require('./Project/Project.js')(randar);

module.exports = randar;
