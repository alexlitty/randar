module.exports = (randar) => {
    randar.monitor = function(ctx, object, width, height) {
        return (new randar.Monitor(ctx, object, width, height));
    };

    randar.Monitor = function(ctx, object, width, height) {
        this.ctx    = ctx;

        this.object = object;
        if (this.object instanceof randar.Project.Item) {
            this.object = this.object.object();
        }

        if (!this.object.kind || !this.object.ctx) {
            throw new Error('Invalid object');
        }

        this.object.ctx(ctx);
        this.win = ctx.window(width || 800, height || 600);

        if (this.object.kind() === 'geometry') {
            this.win.camera().projection();
            this.win.camera().move(randar.vector(0, 0, -10));
            this.win.camera().target(randar.vector(0, 0, 0));
        }

        this.present();
    };

    randar.Monitor.prototype.present = function() {
        this.win.clear();
        this.win.draw(this.object);
        this.win.present();
    };
};
