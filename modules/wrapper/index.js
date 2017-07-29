const randar = require('../adapter');

require('./toColor')(randar);
require('./toVector')(randar);
require('./toVertex')(randar);

require('./Scene/Scene')(randar);
require('./Project/Project')(randar);
require('./Observer/ItemObserver')(randar);

randar.generate = { };
require('./Generate/Shape/Circle')(randar);

module.exports = randar;
