module.exports = (randar) => {
    randar.toVector = (obj) => {
        if (!obj) {
            throw new Error('Invalid conversion to vector');
        }

        // To vector3.
        let result = { };
        if (typeof obj.x !== 'undefined' && obj.y !== 'undefined' && obj.z !== 'undefined') {
            for (c of ['x', 'y', 'z']) {
                if (typeof obj[c] === 'number') {
                    result[c] = obj[c];
                }
                
                else {
                    let converted = parseFloat(obj[c]);
                    if (isNaN(converted)) {
                        throw new Error(`Invalid ${c} value: ${obj[c]}`);
                    }

                    result[c] = converted;
                }
            }

            return randar.vector(result.x, result.y, result.z);
        }

        else if (typeof obj.u !== 'undefined' && obj.v !== 'undefined') {
            for (c of ['u', 'v']) {
                if (typeof obj[c] === 'number') {
                    result[c] = obj[c];
                }
                
                else {
                    let converted = parseFloat(obj[c]);
                    if (isNaN(converted)) {
                        throw new Error(`Invalid ${c} value: ${obj[c]}`);
                    }

                    result[c] = converted;
                }
            }

            return new randar.Vector2_float(result.u, result.v);
        }
    };
};
