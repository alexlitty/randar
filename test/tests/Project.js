describe('Project', function() {
    let tmpDir;

    before(function() {
        tmpDir = randar.tempDirectory();
    });

    it('constructs new project', function() {
        let project = randar.project();
        assert.equal(project.directory().toString(), '.');
        assert.equal(project._onDisk, false);
    });

    it('saves', function() {
        let project = randar.project();
        project.directory(tmpDir);
        assert.equal(project._onDisk, false);

        project.save();
        assert.equal(project._onDisk, true);
    });

    it('loads', function() {
        let project = randar.project(tmpDir);
        assert.equal(project._onDisk, true);
        assert.equal(project.directory().toString(), tmpDir.toString());
    });
});
