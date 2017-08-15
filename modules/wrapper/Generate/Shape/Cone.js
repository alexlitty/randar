module.exports = (randar) => {
    randar.generate.cone = function(options) {
        let palette = options.palette || randar.palette.Default;
        let geometry = randar.geometry();

        let hr = options.height / 2;
        let quat = randar.quaternion(
            randar.vector(0, 1, 0),
            randar.angle((1 / options.faces) * randar.TWO_PI)
        );

        let tip = randar.vertex(randar.vector(0, hr, 0));

        let base = [];
        let baseVector = randar.vector(options.radius, -hr, 0);
        for (let i = 0; i < options.faces; i++) {
            if (i > 0) {
                baseVector = quat.transform(baseVector);
            }

            base.push(randar.vertex(baseVector));
        }

        // Side options.faces.
        for (let i = 0; i < options.faces; i++) {
            let current = base[i];

            let previous;
            if (i == 0) {
                previous = base[options.faces - 1];
            } else {
                previous = base[i - 1];
            }

            current.color = previous.color = tip.color = palette.sample();
            geometry.append(current);
            geometry.append(previous);
            geometry.append(tip);
        }

        // Base options.faces.
        let baseCenter = randar.vertex(randar.vector(0, -hr, 0));
        let baseColor = palette.sample();
        for (let i = 0; i < options.faces; i++) {
            let current = base[i];

            let previous;
            if (i == 0) {
                previous = base[options.faces - 1];
            } else {
                previous = base[i - 1];
            }

            baseCenter.color = current.color = previous.color = baseColor;

            geometry.append(baseCenter);
            geometry.append(current);
            geometry.append(previous);
        }

        return geometry;
    }
}
