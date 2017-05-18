describe('VertexBuffer', function() {
    let ctx;
    let buffer;

    beforeEach(function() {
        ctx    = new randar.GraphicsContext();
        buffer = ctx.vertexBuffer();
    });

    it('constructs empty and initialized', function() {
        assert(buffer.isInitialized());
    });
});
