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
    assert.equal(actual.r().toFixed(2), expected.r().toFixed(2));
    assert.equal(actual.g().toFixed(2), expected.g().toFixed(2));
    assert.equal(actual.b().toFixed(2), expected.b().toFixed(2));
    assert.equal(actual.a().toFixed(2), expected.a().toFixed(2));
}

describe('Image', function() {
    it('reflects', function() {
        assert.equal(randar.image().kind(), 'image');
    });

    describe('construction', function() {
        it('default constructs dimensionless', function() {
            assertDimensions(new randar.Image(), 0, 0);
        });

        it('constructs with specific dimensions', function() {
            assertDimensions(new randar.Image(32, 75), 32, 75);
        });

        it('copy constructs deeply', function() {
            const a = new randar.Image();
            const v1 = 0.3499999940395355;
            const v2 = 0.7400000095367432;

            a.resize(1, 1);
            a.setPixel(0, 0, v1, v1, v1, v1);

            const b = new randar.Image(a);
            assert.equal(a.getWidth(), b.getWidth());
            assert.equal(a.getHeight(), b.getHeight());
            assert.notEqual(a.raw(), b.raw());
            assert.equal(a.rawCount(), b.rawCount());

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

    describe('pixels', function() {
        describe('setting', function() {
            function setTest(alphaProvided, mutate, read) {
                const image = new randar.Image();
                image.resize(64, 64);

                const otherColor  = new randar.Color();
                const targetColor = new randar.Color(
                    0.34,
                    0.74,
                    0.44,
                    alphaProvided ? 0.85 : 1
                );
                const target      = { x: 15, y: 31 };

                forEachPixel(image, (x, y) => {
                    mutate(image, x, y, otherColor);
                });

                mutate(image, target.x, target.y, targetColor);
                forEachPixel(image, (x, y) => {
                    let expectedColor;
                    if (target.x === x && target.y === y) {
                        expectedColor = targetColor;
                    } else {
                        expectedColor = otherColor;
                    }

                    assertColor(read(image, x, y), expectedColor);
                });
            }

            it('non-vector & color object arguments', function() {
                setTest(
                    true,
                    (image, x, y, color) => image.setPixel(x, y, color),
                    (image, x, y)        => image.getPixel(x, y)
                );
            });

            it('non-vector & color channel arguments', function() {
                for (alphaProvided of [true, false]) {
                    setTest(
                        alphaProvided,
                        (image, x, y, color) => image.setPixel(
                            x,
                            y,
                            color.r(),
                            color.g(),
                            color.b(),
                            color.a()
                        ),

                        (image, x, y) => image.getPixel(x, y)
                    );
                }
            });

            it('vector & color object arguments', function() {
                setTest(
                    true,
                    (image, x, y, color) => image.setPixel(
                        new randar.Vector2_uint32(x, y),
                        color
                    ),

                    (image, x, y) => image.getPixel(
                        new randar.Vector2_uint32(x, y)
                    )
                );
            });

            it('vector & color channel arguments', function() {
                for (alphaProvided of [true, false]) {
                    setTest(
                        alphaProvided,
                        (image, x, y, color) => image.setPixel(
                            new randar.Vector2_uint32(x, y),
                            color.r(),
                            color.g(),
                            color.b(),
                            color.a()
                        ),

                        (image, x, y) => image.getPixel(
                            new randar.Vector2_uint32(x, y)
                        )
                    );
                }
            });
        });
    });

    describe('sizing', function() {
        it('stays dimensionless with zero width or height', function() {
            const image = new randar.Image();
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
                assert.equal(image.rawCount(), 0);
                assert.equal(image.hasDimensions(), false);
            }
        });

        it('reports correct dimensions after resizing', function() {
            const image = new randar.Image();

            image.resize(33, 55);
            assert.equal(image.getWidth(), 33);
            assert.equal(image.getHeight(), 55);
        });

        it('maintains correct raw size', function() {
            const image = new randar.Image();

            image.resize(1, 1);
            assert.equal(image.rawCount(), 4);

            image.resize(4, 4);
            assert.equal(image.rawCount(), 64);

            image.resize(3, 1);
            assert.equal(image.rawCount(), 12);

            for (var x = 1; x < 64; x++) {
                for (var y = 1; y < 64; y++) {
                    image.resize(x, y);
                    assert.equal(image.getWidth(), x);
                    assert.equal(image.getHeight(), y);
                    assert.equal(image.rawCount(), x * y * 4);
                }
            }
        });

        it('accepts reasonably large sizes', function() {
            const image = new randar.Image();

            image.resize(1024, 768);
            assert.equal(image.getWidth(), 1024);
            assert.equal(image.getHeight(), 768);
            assert.equal(image.rawCount(), 3145728);
            
            image.resize(10000, 10000);
            assert.equal(image.getWidth(), 10000);
            assert.equal(image.getHeight(), 10000);
            assert.equal(image.rawCount(), 400000000);
        });

        it('rejects ridiculously large sizes', function() {
            const image = new randar.Image();

            assert.throws(() => image.resize(5000000000, 1));
            assert.throws(() => image.resize(1, 5000000000));
            assert.throws(() => image.resize(5000000000, 5000000000));
        });

        it('rejects negative sizes', function() {
            const image = new randar.Image();
            assert.throws(() => image.resize(-1, 19));
            assert.throws(() => image.resize(75, -105));
            assert.throws(() => image.resize(-66, -45));
        });

        it('rejects numeric strings', function() {
            const image = new randar.Image();
            assert.throws(() => image.resize('64', 19));
            assert.throws(() => image.resize(5, '3'));
            assert.throws(() => image.resize('114', '63'));
        });
        
        it('rejects nonsensical sizes', function() {
            const image = new randar.Image();
            assert.throws(() => image.resize(45, null));
            assert.throws(() => image.resize(undefined, 9));
            assert.throws(() => image.resize(NaN, 64));
            assert.throws(() => image.resize(5, Infinity));
            assert.throws(() => image.resize(-Infinity, 19));
        });
    });

    describe.only('i/o', function() {
        let pngFilepath;
        let pngWidth  = 64;
        let pngHeight = 86;
        let pngColor;

        before(function() {
            pngFilepath = randar.globalTempDirectory().child("test.png");
            pngColor    = randar.color(0.5, 0.0, 0.4);
        });

        it('saves to file', function() {
            let image = randar.image(pngWidth, pngHeight);

            for (let x = 0; x < image.getWidth(); x++) {
                for (let y = 0; y < image.getHeight(); y++) {
                    image.setPixel(x, y, pngColor);
                }
            }

            image.save(pngFilepath);
        });

        it('loads from file', function() {
            let = image = randar.image(pngFilepath);

            assert.equal(image.getWidth(), pngWidth);
            assert.equal(image.getHeight(), pngHeight);

            for (let x = 0; x < image.getWidth(); x++) {
                for (let y = 0; y < image.getHeight(); y++) {
                    assertColor(image.getPixel(x, y), pngColor);
                }
            }
        });
    });
});
