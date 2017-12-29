describe('GraphicsContext', function() {
    it('constructs with OpenGL 4.5', function() {
        assert(/^4.5 ?/.test(randar.context().version()));
    });
});
