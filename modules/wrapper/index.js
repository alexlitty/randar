const randar = require('../adapter');

require('./toVector')(randar);
require('./Project/Project')(randar);

module.exports = randar;
