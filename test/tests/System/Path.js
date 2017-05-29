describe('Path', function() {
    it('default constructs current directory', function() {
        assert.equal(randar.path().toString(), '.');
        assert.equal(randar.path('').toString(), '.');
    });

    it('constructs from string', function() {
        assert.equal(randar.path('/tmp/randar').toString(), '/tmp/randar');
    });

    it('sets from string', function() {
        let logPath = randar.path('/var/log/sys.log');
        logPath.set('/var/log/randar.log');

        assert.equal(logPath.toString(), '/var/log/randar.log');
    });

    it('gets absolute parent path', function() {
        let fooPath = randar.path('/foo/bar/foobar.o');
        assert.equal(fooPath.toString(), '/foo/bar/foobar.o');

        fooPath = fooPath.parent();
        assert.equal(fooPath.toString(), '/foo/bar');

        fooPath = fooPath.parent();
        assert.equal(fooPath.toString(), '/foo');

        fooPath = fooPath.parent();
        assert.equal(fooPath.toString(), '/');
        assert.throws(() => fooPath.parent());
    });

    it('gets relative parent path', function() {
        let fooPath = randar.path('..');
        assert.equal(fooPath.parent().toString(), '../..');

        fooPath.set('/foo/bar/..');
        assert.equal(fooPath.parent().toString(), '/foo/bar/../..');

        fooPath.set('.');
        assert.equal(fooPath.parent().toString(), '..');

        fooPath.set('./foo/bar');
        assert.equal(fooPath.parent().toString(), './foo');
        assert.equal(fooPath.parent().parent().toString(), '.');

        fooPath.set('~/foo/bar');
        assert.equal(fooPath.parent().toString(), '~/foo');
        assert.equal(fooPath.parent().parent().toString(), '~');
    });

    it('gets child path', function() {
        let fooPath = randar.path('/foo/bar');
        assert.equal(fooPath.child('test').toString(), '/foo/bar/test');

        fooPath.set('/');
        assert.equal(fooPath.child('test').toString(), '/test');

        fooPath.set('');
        assert.equal(fooPath.child('test').toString(), './test');
    });
});
