const randar = require('../adapter');

require('./toColor')(randar);
require('./toVector')(randar);
require('./toVertex')(randar);

require('./Scene/Scene')(randar);
require('./Project/Project')(randar);
require('./Observer/ItemObserver')(randar);

randar.generate = { };

require('./Generate/Shape/Rectangle')(randar);
require('./Generate/Shape/Square')(randar);
require('./Generate/Shape/Cuboid')(randar);
require('./Generate/Shape/Cube')(randar);

require('./Generate/Shape/Circle')(randar);
require('./Generate/Shape/Sphere')(randar);

module.exports = randar;
