describe('Geometry', function() {
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

    it('accepts vertices and indices directly', function() {
        geo.vertices.append(randar.vertex(1, 2, 3));
        geo.vertices.append(randar.vertex(4, 5, 6));
        geo.vertices.append(randar.vertex(7, 8, 9));

        assert.equal(geo.vertices.count(), 3);
        assert.equal(geo.useVertex(randar.vertex(4, 5, 6)), 1);

        geo.sync();
        assert.equal(geo.vertices.count(), 3);
        assert.equal(geo.useVertex(randar.vertex(4, 5, 6)), 1);

        geo.indices.append(0);
        geo.indices.append(1);
        geo.indices.append(2);

        geo.indices.append(1);
        geo.indices.append(2);
        geo.indices.append(0);

        assert.equal(geo.indices.count(), 6);

        geo.sync();
        assert.equal(geo.vertices.count(), 3);
        assert.equal(geo.indices.count(), 6);

        let vertex = geo.vertices.query(2);
        assert.equal(vertex.position.x, 7);
        assert.equal(vertex.position.y, 8);
        assert.equal(vertex.position.z, 9);

        assert.equal(geo.indices.query(4), 2);
    });

    it('accepts vertices with useVertex', function() {
        const vertices = [
            randar.vertex(0, 1, 2),
            randar.vertex(3, 4, 5),
            randar.vertex(6, 7, 8),
            randar.vertex(9, 0.1, 0.2)
        ];

        for (vertex of vertices) {
            geo.useVertex(vertex);
        }

        geo.indices.append(0);
        geo.indices.append(1);
        geo.indices.append(2);
        geo.indices.append(3);

        assert.equal(geo.vertices.count(), 4);
        assert.equal(geo.indices.count(), 4);

        geo.sync();
        assert.equal(geo.vertices.count(), 4);
        assert.equal(geo.indices.count(), 4);

        for (vertex of vertices) {
            assert(geo.vertices.has(vertex));
        }
    });

    it('accepts shape by appending vertices', function() {
        geo.append(randar.vertex(4, 5, 6));
        geo.append(randar.vertex(9, 7, 4));
        geo.append(randar.vertex(4, 5, 6));

        assert.equal(geo.vertices.count(), 2);
        assert.equal(geo.indices.count(), 3);

        geo.sync();
        assert.equal(geo.vertices.count(), 2);
        assert.equal(geo.indices.count(), 3);

        assert.equal(geo.vertices.find(randar.vertex(4, 5, 6)), 0);
        assert.equal(geo.vertices.find(randar.vertex(9, 7, 4)), 1);
    });

    it('draws to off-screen framebuffer', function() {
        geo.append(randar.vertex(0.5, -0.5, -0.5));
        geo.append(randar.vertex(0.5, 0.5, -0.5));
        geo.append(randar.vertex(-0.5, 0.5, -0.5));

        let fb      = ctx.framebuffer();
        let texture = ctx.texture(64, 64);
        fb.attach(texture);

        geo.drawTo(fb);
    });

    it('draws to default framebuffer', function() {
        this.timeout(10000);

        geo.append(randar.vertex(0.5, -0.5, 0.5));
        geo.append(randar.vertex(0.5, 0.5, 0.5));
        geo.append(randar.vertex(-0.5, 0.5, 0.5));

        let win = ctx.window(256, 256);
        let fb = win.framebuffer();

        for (let i = 0; i < 100; i++) {
            fb.clear(randar.color(0.3, 0.3, 0.6));
            geo.drawTo(fb);
            win.present();
        }
    });
});
