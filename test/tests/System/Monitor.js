describe('Monitor', function() {
    let ctx;

    before(function() {
        ctx = new randar.GraphicsContext();
    });

    it('presents geometry', function() {
        this.timeout(10000);
        let geo = ctx.geometry();

        geo.append(randar.vertex(-3, -3, 0));
        geo.append(randar.vertex(-3, 3, 0));
        geo.append(randar.vertex(3, 3, 0));

        let monitor = ctx.monitor(geo);
        monitor.window().fps(24);

        for (let i = 0; i < 48; i++) {
            monitor.window().camera().move(randar.vector(0, 0, 0.05));
            monitor.present();
        }

        monitor.window().close();
    });
});
