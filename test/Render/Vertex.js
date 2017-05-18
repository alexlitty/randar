function assertVertex(vertex, x, y, z, r, g, b, a)
{
    assert.equal(vertex.position.x, x);
    assert.equal(vertex.position.y, y);
    assert.equal(vertex.position.z, z);

    assert.equal(vertex.color.r().toFixed(2), r.toFixed(2));
    assert.equal(vertex.color.g().toFixed(2), g.toFixed(2));
    assert.equal(vertex.color.b().toFixed(2), b.toFixed(2));
    assert.equal(vertex.color.a().toFixed(2), a.toFixed(2));
}

describe.only('Vertex', function() {
    it('constructs with no arguments', function() {
        assertVertex(
            randar.vertex(),
            0, 0, 0,
            0, 0, 0, 1
        );
    });

    it('constructs with position', function() {
        assertVertex(
            randar.vertex(randar.position(1, 2)),
            1, 2, 0,
            0, 0, 0, 1
        );

        assertVertex(
            randar.vertex(randar.position(5, 6, 7)),
            5, 6, 7,
            0, 0, 0, 1
        );
    });

    it('constructs with position and color', function() {
        const positions = [
            randar.position(1, 2),
            randar.position(3, 4, 5)
        ];

        const colors = [
            randar.color(0.9, 0.8, 0.7),
            randar.color(0.6, 0.5, 0.4, 0.3)
        ];

        for (position of positions) {
            for (color of colors) {
                assertVertex(
                    randar.vertex(position, color),
                    position.x, position.y, position.z,
                    color.r(), color.g(), color.b(), color.a()
                );
            }
        }
    });

    it('constructs with position floats', function() {
        assertVertex(
            randar.vertex(1, 2),
            1, 2, 0,
            0, 0, 0, 1
        );

        assertVertex(
            randar.vertex(3, 4, 5),
            3, 4, 5,
            0, 0, 0, 1
        );
    });

    it('constructs with position and color floats', function() {
        assertVertex(
            randar.vertex(1, 2, 3, 0.9, 0.8, 0.7),
            1, 2, 3,
            0.9, 0.8, 0.7, 1
        );

        assertVertex(
            randar.vertex(4, 5, 6, 0.6, 0.5, 0.4, 0.3),
            4, 5, 6,
            0.6, 0.5, 0.4, 0.3
        );
    });
});
