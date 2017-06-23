const randar = require('../adapter');

require('./toColor')(randar);
require('./toVector')(randar);
require('./toVertex')(randar);
require('./Project/Project')(randar);

module.exports = randar;
