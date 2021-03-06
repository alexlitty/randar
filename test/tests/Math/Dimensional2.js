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
                assertDims(new randar[dimName](), 0, 0);
            });

            it('constructs width and height arguments', function() {
                assertDims(new randar[dimName](45, 68), 45, 68);
            });

            it('assigns as reference', function() {
                const a = new randar[dimName](12, 34);
                const b = a;

                assertDims(a, 12, 34);
                assertDims(b, 12, 34);

                b.resize(56, 78);
                assertDims(a, 56, 78);
                assertDims(b, 56, 78);
            });
        });

        describe('usage', function() {
            it('maintains correct width and height after resizing', function() {
                const dims = new randar[dimName]();

                for (var x = 0; x < 127; x++) {
                    for (var y = 0; y < 127; y++) {
                        dims.resize(x, y);
                        assertDims(dims, x, y);
                    }
                }
            });

            it('maintains correct width when changing height', function() {
                const dims = new randar[dimName]();

                dims.setWidth(24);
                for (var y = 0; y < 127; y++) {
                    dims.setHeight(y);
                    assertDims(dims, 24, y);
                }
            });

            it('maintains correct height when changing width', function() {
                const dims = new randar[dimName]();

                dims.setHeight(36);
                for (var x = 0; x < 127; x++) {
                    dims.setWidth(x);
                    assertDims(dims, x, 36);
                }
            });

            it('correctly checks within dimensions', function() {
                const dims = new randar[dimName](4, 5);

                assert(dims.isWithinDimensions(0, 0))
                assert(dims.isWithinDimensions(3, 2))
                assert(dims.isWithinDimensions(3, 4))

                assert(!dims.isWithinDimensions(4, 4))
                assert(!dims.isWithinDimensions(3, 5))
                assert(!dims.isWithinDimensions(4, 5))
                assert(!dims.isWithinDimensions(6, 6))
            });

            it('converts to string', function() {
                const dims = new randar[dimName]();

                for (var x = 0; x < 127; x++) {
                    for (var y = 0; y < 127; y++) {
                        dims.resize(x, y);

                        const result = dims.toString().split('x');
                        assert.equal(result.length, 2);
                        assert.equal(parseInt(result[0]), x);
                        assert.equal(parseInt(result[1]), y);
                    }
                }
            });
        });
    });
});
