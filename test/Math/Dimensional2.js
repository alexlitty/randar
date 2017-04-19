const assert  = require('assert');
const adapter = require('../../modules/adapter');

function assertDims(dims, expectedWidth, expectedHeight) {
    if (expectedWidth === 0 || expectedHeight === 0) {
        assert(!dims.hasDimensions());
    } else {
        assert(dims.hasDimensions());
    }

    assert.equal(dims.getWidth(), expectedWidth);
    assert.equal(dims.getHeight(), expectedHeight);
}

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
                assertDims(new adapter[dimName](), 0, 0);
            });

            it('constructs width and height arguments', function() {
                assertDims(new adapter[dimName](45, 68), 45, 68);
            });

            it('copy constructs deeply', function() {
                const a = new adapter[dimName](12, 34);
                const b = new adapter[dimName](a);
                assertDims(a, 12, 34);
                assertDims(b, 12, 34);

                b.resize(56, 78);
                assertDims(a, 12, 34);
                assertDims(b, 56, 78);
            });
        });

        describe('usage', function() {
            it('maintains correct width and height after resizing', function() {
                const dims = new adapter[dimName]();

                for (var x = 0; x < 127; x++) {
                    for (var y = 0; y < 127; y++) {
                        dims.resize(x, y);
                        assertDims(dims, x, y);
                    }
                }
            });

            it('maintains correct width when changing height', function() {
                const dims = new adapter[dimName]();

                dims.setWidth(24);
                for (var y = 0; y < 127; y++) {
                    dims.setHeight(y);
                    assertDims(dims, 24, y);
                }
            });

            it('maintains correct height when changing width', function() {
                const dims = new adapter[dimName]();

                dims.setHeight(36);
                for (var x = 0; x < 127; x++) {
                    dims.setWidth(x);
                    assertDims(dims, x, 36);
                }
            });
        });
    });
});
