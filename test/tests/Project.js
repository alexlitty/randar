describe.only('Project', function() {
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


        let geo = randar.geometry();
        for (let i = 0; i < 3; i++) {
            geo.append(randar.vertex(0.3, 0.2, 0.1));
        }

        let bin = project.addBin('Primary bin');
        assert.equal(Object.keys(project.bins).length, 1);
        assert.equal(Object.keys(project.binFolders).length, 1);

        project.addBinItem(geo, 'Test Geometry', bin);
        assert.equal(Object.keys(project.binItems).length, 1);

        project.save();
        assert.equal(project._onDisk, true);
    });

    it('loads', function() {
        let project = randar.project(tmpDir);
        assert.equal(project._onDisk, true);
        assert.equal(project.directory().toString(), tmpDir.toString());

        assert.equal(Object.keys(project.bins).length, 1);
        assert.equal(Object.keys(project.binFolders).length, 1);
        assert.equal(Object.keys(project.binItems).length, 1);

        project.loadBinItem(project.binItems[0]);

        let geo = project.binItems[0].object;
        assert.equal(geo.vertices.count(), 1);
        assert.equal(geo.indices.count(), 3);
    });
});
