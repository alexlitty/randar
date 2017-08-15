describe('Draw State', function() {
    it('constructs empty', function() {
        randar.drawState();
        randar.drawState({});
    });

    it('constructs with valid properties', function() {
        randar.drawState({
            transform : randar.transform(),
            skeleton  : randar.skeleton(),
            textures  : randar.textures(),
            lights    : randar.lights()
        });
    });

    it('refuses invalid states', function() {
        assert.throws(() => randar.drawState(94));
        assert.throws(() => randar.drawState({ foobar: randar.transform() }));
    });
});
