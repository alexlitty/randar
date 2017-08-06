module.exports = (randar) => {
    /**
     * Calculates a face's normal.
     *
     * Vertices or vectors may be provided.
     *
     * If normalize is true or omitted, a unit normal is returned.
     */
    randar.normal = function(a, b, c, normalize) {
        if (a.position) {
            a = a.position;
        }

        if (b.position) {
            b = b.position;
        }

        if (c.position) {
            c = c.position;
        }

        let U = b.minus(a);
        let V = c.minus(a);

        let normal = randar.vector(
			(U.y * V.z) - (U.z * V.y),
			(U.z * V.x) - (U.x * V.z),
			(U.x * V.y) - (U.y * V.x)
        );

        if (typeof normalize === 'undefined' || normalize) {
            normal.normalize();
        }

        return normal;
    }
};
