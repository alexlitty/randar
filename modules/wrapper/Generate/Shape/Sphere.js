module.exports = (randar) => {
    randar.generate.sphere = function(options) {
        let palette = options.palette || randar.palette.Default;

        if (options.verticalPoints < 3) {
            throw new Error('Invalid number of vertical points');
        }

        if (options.horizontalPoints < 3) {
            throw new Error('Invalid number of horizontal points');
        }

        let geometry = randar.geometry();

        let verticalQuat = randar.quaternion(
            randar.vector(0, 0, 1),
            randar.angle((1 / (options.verticalPoints-1)) * randar.PI)
        );

        let horizontalQuat = randar.quaternion(
            randar.vector(0, 1, 0),
            randar.angle((1 / options.horizontalPoints) * randar.TWO_PI)
        );

        let rows = [];
        let baseVector = randar.vector(0, options.radius, 0);
        for (let i = 0; i < options.verticalPoints; i++) {
            let row = [];

            if (i > 0) {
                baseVector = verticalQuat.transform(baseVector); 
            }

            let nextVector = baseVector;
            for (let j = 0; j < options.horizontalPoints; j++) {
                nextVector = horizontalQuat.transform(nextVector);
                row.push(randar.vertex(nextVector));
            }

            rows.push(row);
        }

        for (let i = 1; i < rows.length; i++) {
            let previousRow = rows[i - 1];
            let row         = rows[i];

            for (let j = 0; j < row.length; j++) {
                let topLeft;
                let bottomLeft;

                if (j == 0) {
                    topLeft    = previousRow[previousRow.length - 1];
                    bottomLeft = row[row.length - 1];
                } else {
                    topLeft    = previousRow[j - 1];
                    bottomLeft = row[j - 1];
                }

                let topRight    = previousRow[j];
                let bottomRight = row[j];

                topLeft.color = topRight.color = bottomLeft.color = bottomRight.color = palette.sample();

                geometry.append(topLeft);
                geometry.append(bottomRight);
                geometry.append(bottomLeft);

                geometry.append(topLeft);
                geometry.append(topRight);
                geometry.append(bottomRight);
            }
        }

        return geometry;
    }
}
