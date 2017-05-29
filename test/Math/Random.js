describe.only('Random', function() {
    it('generates random floats between [0, 1]', function() {
        for (let i = 0; i < 1000; i++) {
            let result = randar.randomFloat();
            assert(result >= 0 && result <= 1);
        }
    });

    it('generates random floats within bounds', function() {
        for (let i = 0; i < 1000; i++) {
            let result = randar.randomFloat(500, 6000);
            assert(result >= 500 && result <= 6000);

            result = randar.randomFloat(0.2, 0.98);
            assert(result >= 0.2 && result <= 0.98);
        }
    });
});
