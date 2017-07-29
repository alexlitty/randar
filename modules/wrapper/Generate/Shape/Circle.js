module.exports = (randar) => {
    randar.generate.circle = function(radius, points) {
        if (points < 3) {
            throw new Error('Circles can only be generated with 3 or more points');
        }

        let geometry = randar.geometry();

        let quat = randar.quaternion(
            randar.vector(0, 0, 1),
            randar.angle((1 / points) * randar.TWO_PI)
        );

        let center = randar.vector(0, 0, 0);
        let outter = randar.vector(radius, 0, 0);

        let vertex = randar.vertex();
        for (let i = 0; i < points; i++) {
            vertex.position = center;
            geometry.append(vertex);

            vertex.position = outter;
            geometry.append(vertex);

            outter = quat.transform(outter);
            vertex.position = outter;
            geometry.append(vertex);
        }

        return geometry;
    }
};
