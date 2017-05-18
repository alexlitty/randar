function assertVector(vector, x, y, z) {
    assert.equal(vector.x, x);
    assert.equal(vector.y, y);
    assert.equal(vector.z, z);
}

describe.only('Vector3', function() {
    for (let creator of ['vector', 'position']) {
        describe(`via ${creator}`, function() {
            it('constructs with no arguments', function() {
                assertVector(randar[creator](), 0, 0, 0);
            });

            it('constructs with x and y', function() {
                assertVector(randar[creator](6, 7), 6, 7, 0);
            });

            it('constructs with x, y, and z', function() {
                assertVector(randar[creator](3, 29, 66), 3, 29, 66);
            });

            it('refuses construction with 1 argument', function() {
                assert.throws(() => randar[creator](1));
            });
        });
    }
});
