describe.only('Directory', function() {
    let tmp;

    it('returns platform-specific temporary directory', function() {
        assert(randar.platformTempDirectory().toString(), '/tmp');
    });

    it('creates a global temporary directory', function() {
        assert(randar.globalTempDirectory().toString(), '/tmp/randar');
        assert(fs.existsSync('/tmp/randar'));
    });

    it('creates temporary directories', function() {
        tmp = randar.tempDirectory();
        assert(fs.existsSync(tmp.toString()));
    });

    it('creates and removes directories', function() {
        let tmpTest = tmp.child('test');
        randar.createDirectory(tmpTest);
        assert(fs.existsSync(tmpTest.toString()));

        randar.removeDirectory(tmp);
        assert(!fs.existsSync(tmpTest.toString()));
        assert(!fs.existsSync(tmp.toString()));
    });
});
