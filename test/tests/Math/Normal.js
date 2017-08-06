describe.only('Normal', function() {
    it('calculates normals from vectors', function() {
        let normal = randar.normal(
            randar.vector(0, 0, 0),
            randar.vector(0, 2, 0),
            randar.vector(0, 2, 2),
            false
        );

        assert.equal(normal.x, 4);
        assert.equal(normal.y, 0);
        assert.equal(normal.z, 0);
    });

    it('calculates unit normals from vectors', function() {
        let normal = randar.normal(
            randar.vector(0, 0, 0),
            randar.vector(2, 0, 0),
            randar.vector(2, 2, 0)
        );

        assert.equal(normal.x, 0);
        assert.equal(normal.y, 0);
        assert.equal(normal.z, 1);
    });

    it('calculates normals from vertices', function() {
        let normal = randar.normal(
            randar.vertex(0, 0, 0),
            randar.vertex(0, 2, 0),
            randar.vertex(0, 2, 2),
            false
        );

        assert.equal(normal.x, 4);
        assert.equal(normal.y, 0);
        assert.equal(normal.z, 0);
    });

    it('calculates unit normals from vertices', function() {
        let normal = randar.normal(
            randar.vertex(0, 0, 0),
            randar.vertex(2, 0, 0),
            randar.vertex(2, 2, 0)
        );

        assert.equal(normal.x, 0);
        assert.equal(normal.y, 0);
        assert.equal(normal.z, 1);
    });
});
