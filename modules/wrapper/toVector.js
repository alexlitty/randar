module.exports = (randar) => {
    randar.toVector = (obj) => {
        if (!obj) {
            throw new Error('Invalid conversion to vector');
        }

        let result = { };
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
    };
};
