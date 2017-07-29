module.exports = (randar) => {
    randar.generate.sphere = function(geometry, radius, horizontalPoints, verticalPoints) {
        if (verticalPoints < 3) {
            throw new Error('Invalid number of vertical points');
        }

        if (horizontalPoints < 3) {
            throw new Error('Invalid number of horizontal points');
        }

        let verticalQuat = randar.quaternion(
            randar.vector(0, 0, 1),
            randar.angle((1 / (verticalPoints-1)) * randar.PI)
        );

        let horizontalQuat = randar.quaternion(
            randar.vector(0, 1, 0),
            randar.angle((1 / horizontalPoints) * randar.TWO_PI)
        );

        let rows = [];
        let baseVector = randar.vector(0, radius, 0);
        for (let i = 0; i < verticalPoints; i++) {
            let row = [];

            if (i > 0) {
                baseVector = verticalQuat.transform(baseVector); 
            }

            let nextVector = baseVector;
            for (let j = 0; j < horizontalPoints; j++) {
                nextVector = horizontalQuat.transform(nextVector);
                row.push(randar.vertex(nextVector, randar.randomColor()));
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

                geometry.append(topLeft);
                geometry.append(bottomRight);
                geometry.append(bottomLeft);

                geometry.append(topLeft);
                geometry.append(topRight);
                geometry.append(bottomRight);
            }
        }
    }
}
