describe('Execute', function() {
    it('returns correct exit codes', function() {
        assert.equal(randar.execute('test foobar'), 0);
        assert.notEqual(randar.execute('nonexistentcommand'), 0);
    });
});
