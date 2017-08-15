module.exports = (randar) => {
    randar.generate.circle = function(options) {
        let palette = options.palette || randar.palette.Default;

        if (options.points < 3) {
            throw new Error('Circles can only be generated with 3 or more options.points');
        }

        let geometry = randar.geometry();

        let quat = randar.quaternion(
            randar.vector(0, 0, 1),
            randar.angle((1 / options.points) * randar.TWO_PI)
        );

        let center = randar.vector(0, 0, 0);
        let outter = randar.vector(options.radius, 0, 0);

        let vertex = randar.vertex();
        vertex.color = palette.sample();
        for (let i = 0; i < options.points; i++) {
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
