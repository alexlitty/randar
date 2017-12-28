function assertVertex(vertex, other) {
    assert.equal(vertex.position.x.toFixed(2), other.position.x.toFixed(2));
    assert.equal(vertex.position.y.toFixed(2), other.position.y.toFixed(2));
    assert.equal(vertex.position.z.toFixed(2), other.position.z.toFixed(2));

    assert.equal(vertex.color.r().toFixed(2), other.color.r().toFixed(2));
    assert.equal(vertex.color.g().toFixed(2), other.color.g().toFixed(2));
    assert.equal(vertex.color.b().toFixed(2), other.color.b().toFixed(2));
    assert.equal(vertex.color.a().toFixed(2), other.color.a().toFixed(2));
}

describe.only('VertexBuffer', function() {
    let ctx;
    let buffer;
    let vertices;

    before(function() {
        vertices = [
            randar.vertex(0.9, 0.9, 0.2, 0.1, 0.2, 0.3, 0.4),
            randar.vertex(-0.9, 0.9, 0.4, 0.9, 0.8, 0.7, 0.6),
            randar.vertex(-0.9, -0.9, 0.3, 0.5, 0.6, 0.4, 0.9)
        ];
    });

    beforeEach(function() {
        ctx    = new randar.GraphicsContext();
        buffer = new randar.VertexBuffer(ctx);
    });

    it('constructs empty and initialized', function() {
        assert(buffer.isInitialized());
        assert.equal(buffer.count(), 0);
    });

    it('accurately appends vertices', function() {
        for (vertex of vertices) {
            buffer.append(vertex);
        }

        for (let i = 0; i < vertices.length; i++) {
            assertVertex(buffer.get(i), vertices[i]);
        }

        assert.equal(buffer.count(), vertices.length);
        buffer.sync();
        assert.equal(buffer.count(), vertices.length);

        for (let i = 0; i < vertices.length; i++) {
            assertVertex(buffer.get(i), vertices[i]);
            assertVertex(buffer.query(i), vertices[i]);
        }
    });

    it('finds vertices', function() {
        let i = 0;
        for (vertex of vertices) {
            buffer.append(vertex);
            assert(buffer.has(vertices[i]));
            assert.equal(buffer.find(vertices[i]), i);
            i++;
        }

        for (let i = 0; i < vertices.length; i++) {
            assert(buffer.has(vertices[i]));
            assert.equal(buffer.find(vertices[i]), i);
        }
    });
});
