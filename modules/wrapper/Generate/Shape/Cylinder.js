module.exports = (randar) => {
    randar.generate.cylinder = function(radius, height, faces, palette) {
        palette = palette || randar.palette.Default;
        let geometry = randar.geometry();

        let hr = height / 2;

        let quat = randar.quaternion(
            randar.vector(0, 1, 0),
            randar.angle((1 / faces) * randar.TWO_PI)
        );

        let rows = [[], []];
        let vector = randar.vector(radius, 0, 0);
        for (let i = 0; i < faces; i++) {
            if (i > 0) {
                vector = quat.transform(vector);
            }

            vector.y = -hr;
            rows[0].push(randar.vertex(vector));

            vector.y = hr;
            rows[1].push(randar.vertex(vector));
        }

        // Top and bottom faces.
        for (let k = 0; k <= 1; k++) {
            let color = palette.sample();
            for (let i = 0; i < faces; i++) {
                let current = rows[k][i];
                let center = randar.vertex(randar.vector(0, current.position.y, 0));

                let previous;
                if (i == 0) {
                    previous = rows[k][faces - 1];
                } else {
                    previous = rows[k][i - 1];
                }

                current.color = previous.color = center.color = color;
                geometry.append(center);
                geometry.append(current);
                geometry.append(previous);
            }
        }

        // Middle faces.
        for (let i = 0; i < faces; i++) {
            let topRight    = rows[0][i];
            let bottomRight = rows[1][i];

            let topLeft, bottomLeft;
            if (i == 0) {
                topLeft = rows[0][faces - 1];
                bottomLeft = rows[1][faces - 1];
            } else {
                topLeft = rows[0][i - 1];
                bottomLeft = rows[1][i - 1];
            }

            topLeft.color = topRight.color = bottomLeft.color = bottomRight.color = palette.sample();

            geometry.append(topLeft);
            geometry.append(topRight);
            geometry.append(bottomRight);

            geometry.append(topLeft);
            geometry.append(bottomRight);
            geometry.append(bottomLeft);
        }

        return geometry;
    }
}
