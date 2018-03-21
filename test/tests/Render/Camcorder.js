describe('Camcorder', function() {
    let win;

    before(function() {
        win = new randar.Window(600, 480);
    });

    after(function() {
        win.close();
    });

    it('saves to video', function() {
        this.timeout(20000);
        let camcorder = win.camcorder();

        let color = randar.color();
        let i = 0;
        for (let i = 0; i <= 48; i++) {
            color.rInt(i * 5);
            color.bInt(i * 5);

            win.clear(color);
            win.present();
            assert.equal(camcorder.count(), i + 1);
        }

        camcorder.save(randar.globalTempDirectory().child('test.mp4'));
    });
});
