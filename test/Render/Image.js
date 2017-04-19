const assert  = require('assert');
const adapter = require('../../modules/adapter');

function forEachPixel(image, routine) {
    for (var x = 0; x < image.getWidth(); x++) {
        for (var y = 0; y < image.getHeight(); y++) {
            routine(x, y);
        }
    }
}

function assertDimensions(image, width, height) {
    if (width === 0 || height === 0) {
        assert(!image.hasDimensions());
    } else {
        assert(image.hasDimensions());
    }
    assert.equal(image.getWidth(), width);
    assert.equal(image.getHeight(), height);
}

function assertColor(actual, expected) {
    assert.equal(actual.r(), expected.r());
    assert.equal(actual.g(), expected.g());
    assert.equal(actual.b(), expected.b());
    assert.equal(actual.a(), expected.a());
}

describe('Image', function() {
    describe('construction', function() {
        it('default constructs dimensionless', function() {
            assertDimensions(new adapter.Image(), 0, 0);
        });

        it('copy constructs deeply', function() {
            const a = new adapter.Image();
            const v1 = 0.3499999940395355;
            const v2 = 0.7400000095367432;

            a.resize(1, 1);
            a.setPixel(0, 0, v1, v1, v1, v1);

            const b = new adapter.Image(a);
            assert.equal(a.getWidth(), b.getWidth());
            assert.equal(a.getHeight(), b.getHeight());
            assert.notEqual(a.raw(), b.raw());
            assert.equal(a.rawSize(), b.rawSize());

            var pixel = b.getPixel(0, 0);
            assert.equal(pixel.r(), v1);
            assert.equal(pixel.g(), v1);
            assert.equal(pixel.b(), v1);
            assert.equal(pixel.a(), v1);

            b.setPixel(0, 0, v2, v2, v2, v2);
            pixel = b.getPixel(0, 0);
            assert.equal(pixel.r(), v2);
            assert.equal(pixel.g(), v2);
            assert.equal(pixel.b(), v2);
            assert.equal(pixel.a(), v2);

            pixel = a.getPixel(0, 0);
            assert.equal(pixel.r(), v1);
            assert.equal(pixel.g(), v1);
            assert.equal(pixel.b(), v1);
            assert.equal(pixel.a(), v1);
        });
    });

    describe('mutation', function() {
        it('setting pixels, non-vector & color object arguments', function() {
            const image = new adapter.Image();
            image.resize(64, 64);

            const otherColor  = new adapter.Color();
            const targetColor = new adapter.Color(0.34, 0.74, 0.44, 0.01);

            const target = { x: 31, y: 5 };
            forEachPixel(image, (x, y) => {
                image.setPixel(x, y, otherColor);
            });

            image.setPixel(target.x, target.y, targetColor);
            forEachPixel(image, (x, y) => {
                const color = image.getPixel(x, y);
                let checkColor;
                assertColor(
                    image.getPixel(x, y),
                    (target.x === x && target.y === y) ? targetColor : otherColor
                );
            });
        });

        it('targets correct pixel with Vector2 argument', function() {
            /*const image new adapter.Image();
            image.resize(64, 64);

            const */
        });
    });

    describe('sizing', function() {
        it('stays dimensionless with zero width or height', function() {
            const image = new adapter.Image();
            const sizes = [
                { x: 0, y: 0 },
                { x: 0, y: 1 },
                { x: 1, y: 0 }
            ];

            for (size of sizes) {
                image.resize(size.x, size.y);
                assert.equal(image.getWidth(), size.x);
                assert.equal(image.getHeight(), size.y);

                assert.equal(image.raw(), null);
                assert.equal(image.rawSize(), 0);
                assert.equal(image.hasDimensions(), false);
            }
        });

        it('reports correct dimensions after resizing', function() {
            const image = new adapter.Image();

            image.resize(33, 55);
            assert.equal(image.getWidth(), 33);
            assert.equal(image.getHeight(), 55);
        });

        it('maintains correct raw size', function() {
            const image = new adapter.Image();

            image.resize(1, 1);
            assert.equal(image.rawSize(), 4);

            image.resize(4, 4);
            assert.equal(image.rawSize(), 64);

            image.resize(3, 1);
            assert.equal(image.rawSize(), 12);

            for (var x = 1; x < 64; x++) {
                for (var y = 1; y < 64; y++) {
                    image.resize(x, y);
                    assert.equal(image.getWidth(), x);
                    assert.equal(image.getHeight(), y);
                    assert.equal(image.rawSize(), x * y * 4);
                }
            }
        });

        it('accepts reasonably large sizes', function() {
            const image = new adapter.Image();

            image.resize(1024, 768);
            assert.equal(image.getWidth(), 1024);
            assert.equal(image.getHeight(), 768);
            assert.equal(image.rawSize(), 3145728);
            
            image.resize(10000, 10000);
            assert.equal(image.getWidth(), 10000);
            assert.equal(image.getHeight(), 10000);
            assert.equal(image.rawSize(), 400000000);
        });

        it('rejects ridiculously large sizes', function() {
            const image = new adapter.Image();

            assert.throws(() => image.resize(5000000000, 1));
            assert.throws(() => image.resize(1, 5000000000));
            assert.throws(() => image.resize(5000000000, 5000000000));
        });

        it('rejects negative sizes', function() {
            const image = new adapter.Image();
            assert.throws(() => image.resize(-1, 19));
            assert.throws(() => image.resize(75, -105));
            assert.throws(() => image.resize(-66, -45));
        });

        it('rejects numeric strings', function() {
            const image = new adapter.Image();
            assert.throws(() => image.resize('64', 19));
            assert.throws(() => image.resize(5, '3'));
            assert.throws(() => image.resize('114', '63'));
        });
        
        it('rejects nonsensical sizes', function() {
            const image = new adapter.Image();
            assert.throws(() => image.resize(45, null));
            assert.throws(() => image.resize(undefined, 9));
            assert.throws(() => image.resize(NaN, 64));
            assert.throws(() => image.resize(5, Infinity));
            assert.throws(() => image.resize(-Infinity, 19));
        });
    });
});
