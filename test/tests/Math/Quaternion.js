describe('Quaternion', function() {
    describe('construction', function() {
        it('accepts no parameters', function() {
            let quat = randar.quaternion();
            assert.equal(quat.axis().x, 0);
            assert.equal(quat.axis().y, 0);
            assert.equal(quat.axis().z, 0);
            assert.equal(quat.angle().toRadians(), randar.angle(0).toRadians());
        });

        it('accepts axis parameter', function() {
            let quat = randar.quaternion(randar.vector(0, 0, 1));
            assert.equal(quat.axis().x, 0);
            assert.equal(quat.axis().y, 0);
            assert.equal(quat.axis().z, 1);
        });

        it('accepts axis and angle parameters', function() {
            let quat = randar.quaternion(randar.vector(0, 1, 0), randar.angle(1.09));
            assert.equal(quat.axis().x, 0);
            assert.equal(quat.axis().y, 1);
            assert.equal(quat.axis().z, 0);
            assert.equal(
                quat.angle().toRadians().toFixed(2),
                randar.angle(1.09).toRadians().toFixed(2)
            );

            quat = randar.quaternion(randar.vector(0.1, 0.5, 0.3), randar.angle(0.3));
            assert.equal(quat.axis().x.toFixed(2), '0.17');
            assert.equal(quat.axis().y.toFixed(2), '0.85');
            assert.equal(quat.axis().z.toFixed(2), '0.51');
            assert.equal(
                quat.angle().toRadians().toFixed(2),
                randar.angle(0.3).toRadians().toFixed(2)
            );
        });
    });

    it('transforms vectors', function() {
        let quat = randar.quaternion(randar.vector(0, 1, 0), randar.angle(0.3));

        let result = quat.transform(randar.vector(0, 5, 0));
        assert.equal(result.x, 0);
        assert.equal(result.y, 5);
        assert.equal(result.z, 0);

        result = quat.transform(randar.vector(1, 5, 0));
        assert.equal(result.x.toFixed(2), '0.96');
        assert.equal(result.y.toFixed(2), '5.00');
        assert.equal(result.z.toFixed(2), '0.30');
    });
});
