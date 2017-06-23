const randar = require('../adapter');

require('./toColor')(randar);
require('./toVector')(randar);
require('./Project/Project')(randar);

module.exports = randar;
