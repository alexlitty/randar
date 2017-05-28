describe.only('Camcorder', function() {
    let ctx;
    let win;

    before(function() {
        ctx = new randar.GraphicsContext();
        win = ctx.window(600, 480);
    });

    after(function() {
        win.close();
    });

    it('saves to video', function() {
        this.timeout(30000);
        let camcorder = win.camcorder();

        let color = randar.color();
        for (let channel = 0; channel <= 255; channel++) {
            color.rInt(channel);
            color.bInt(channel);

            win.clear(color);
            win.present();
            assert.equal(camcorder.count(), channel + 1);
        }
    });
});
