const randar = require('../adapter');

require('./color-ext')(randar);
require('./vertex')(randar);

module.exports = randar;
