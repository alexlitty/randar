describe.only('Directory', function() {
    it('temporary directory is provided', function() {
        let tmp = randar.Directory.Temp.toString();
        assert(tmp.length);
        assert(path.basename(tmp).length);
    });

    it('creates itself on the filesystem', function() {
        let tmp = randar.Directory.Temp.toString();

        if (fs.existsSync(tmp)) {
            fs.rmdirSync(tmp);
            assert(!fs.existsSync(tmp));
        }

        randar.Directory.Temp.create();
        assert(fs.existsSync(tmp));
    });
});
