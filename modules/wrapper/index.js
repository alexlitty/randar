const randar = require('../adapter');

// Conversion helpers.
require('./toColor')(randar);
require('./toVector')(randar);
require('./toVertex')(randar);

// Color palettes.
randar.palette = { };

require('./Palette/Fixed.js')(randar);
require('./Palette/Varying.js')(randar);
require('./Palette/Default.js')(randar);

// Geometry generation.
randar.generate = { };

require('./Generate/Shape/Rectangle')(randar);
require('./Generate/Shape/Square')(randar);
require('./Generate/Shape/Cuboid')(randar);
require('./Generate/Shape/Cube')(randar);

require('./Generate/Shape/Circle')(randar);
require('./Generate/Shape/Sphere')(randar);

require('./Generate/Shape/Cylinder')(randar);

// Miscellaneous.
require('./Scene/Scene')(randar);
require('./Project/Project')(randar);
require('./Observer/ItemObserver')(randar);

// Seed the simple random engine.
randar.seedRandomWithTime();

module.exports = randar;
