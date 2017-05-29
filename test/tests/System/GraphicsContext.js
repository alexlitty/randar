describe('GraphicsContext', function() {
    it('constructs with OpenGL 4.5', function() {
        let ctx = new randar.GraphicsContext();
        assert(/^4.5 ?/.test(ctx.version()));
    });
});
