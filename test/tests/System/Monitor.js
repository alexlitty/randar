describe('Monitor', function() {
    let ctx;

    before(function() {
        ctx = new randar.GraphicsContext();
    });

    it('presents geometry', function() {
        this.timeout(10000);
        let geo = randar.generate.sphere(0.5, 16, 16);

        let monitor = ctx.monitor(geo);
        monitor.window().fps(24);

        for (let i = 0; i < 48; i++) {
            monitor.window().camera().move(randar.vector(0, 0, 0.05));
            monitor.present();
        }

        monitor.window().close();
    });
});
