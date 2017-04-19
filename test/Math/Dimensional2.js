const assert  = require('assert');
const adapter = require('../../modules/adapter');

[
    'float',

    'int8',
    'int16',
    'int32',
    'int64',

    'uint8',
    'uint16',
    'uint32',
    'uint64'
].forEach(type => {
    const dimName = `Dimensional2_${type}`;

    describe(dimName, function() {
        describe('construction', function() {
            it('default constructs zero width and height', function() {
                const dims = new adapter[dimName]();
                assert(!dims.hasDimensions());
                assert.equal(dims.getWidth(), 0);
                assert.equal(dims.getHeight(), 0);
            });
        });
    });
});
