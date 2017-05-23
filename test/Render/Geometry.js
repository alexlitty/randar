function assertColor(color, other) {
    assert.equal(color.r().toFixed(2), other.r().toFixed(2));
    assert.equal(color.g().toFixed(2), other.g().toFixed(2));
    assert.equal(color.b().toFixed(2), other.b().toFixed(2));
    assert.equal(color.a().toFixed(2), other.a().toFixed(2));
}


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
        let vertices = [
            randar.vertex(4, 5, 6),
            randar.vertex(9, 7, 4)
        ];

        geo.append(vertices[0]);
        geo.append(vertices[1]);
        geo.append(vertices[0]);

        assert.equal(geo.vertices.count(), 2);
        assert.equal(geo.indices.count(), 3);

        geo.sync();
        assert.equal(geo.vertices.count(), 2);
        assert.equal(geo.vertices.find(randar.vertex(4, 5, 6)), 0);
        assert.equal(geo.vertices.find(randar.vertex(9, 7, 4)), 1);

        for (let i = 0; i < vertices.length; i++) {
            let vertex = geo.vertices.query(i);
            assert.equal(vertex.position.x, vertices[i].position.x);
            assert.equal(vertex.position.y, vertices[i].position.y);
            assert.equal(vertex.position.z, vertices[i].position.z);

            assert.equal(vertex.color.r(), vertices[i].color.r());
            assert.equal(vertex.color.g(), vertices[i].color.g());
            assert.equal(vertex.color.b(), vertices[i].color.b());
            assert.equal(vertex.color.a(), vertices[i].color.a());
        }

        assert.equal(geo.indices.count(), 3);
        assert.equal(geo.indices.query(0), 0);
        assert.equal(geo.indices.query(1), 1);
        assert.equal(geo.indices.query(2), 0);
    });

    it('draws to off-screen framebuffer', function() {
        let fb      = ctx.framebuffer();
        let texture = ctx.texture(64, 64);
        let image   = randar.image();
        let pixel;

        let bgColor = randar.color(0.2, 0, 0.2);
        let fgColor = randar.color(1, 1, 1);

        geo.primitive = randar.Primitive_Point;
        geo.append(randar.vertex(randar.position(-1, 1, 0), fgColor));

        fb.attach(texture);
        fb.clear(bgColor);
        geo.drawTo(fb);

        fb.read(image);
        for (let x = 0; x < texture.getWidth(); x++) {
            for (let y = 0; y < texture.getHeight(); y++) {
                pixel = image.getPixel(x, y);

                if (x == 0 && y == 0) {
                    assertColor(pixel, fgColor);
                } else {
                    assertColor(pixel, bgColor);
                }
            }
        }

        geo.primitive = randar.Primitive_Triangle;
        geo.append(randar.vertex(randar.position(1, 1, 0), fgColor));
        geo.append(randar.vertex(randar.position(1, -1, 0), fgColor));

        fb.clear(bgColor);
        fb.read(image);
        for (let x = 0; x < texture.getWidth(); x++) {
            for (let y = 0; y < texture.getHeight(); y++) {
                assertColor(image.getPixel(x, y), bgColor);
            }
        }

        geo.drawTo(fb);
        fb.read(image);
        for (let x = 0; x < texture.getWidth(); x++) {
            assertColor(image.getPixel(x, 0), fgColor);

            if (x < 60) {
                assertColor(image.getPixel(x, 63), bgColor);
            }
        }

        for (let y = 0; y < texture.getHeight(); y++) {
            assertColor(image.getPixel(63, y), fgColor);

            if (y > 4) {
                assertColor(image.getPixel(0, y), bgColor);
            }
        }
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
