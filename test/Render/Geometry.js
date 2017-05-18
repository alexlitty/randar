describe.only('Geometry', function() {
    let ctx;
    let geo;

    beforeEach(function() {
        ctx = new randar.GraphicsContext();
        geo = ctx.geometry();
    });

    it('constructs initialized and empty', function() {
        assert.equal(geo.vertices.count(), 0);
        assert.equal(geo.indices.count(), 0);
    });
});
