describe('Project', function() {
    let tmpDir;

    before(function() {
        tmpDir = randar.tempDirectory();
    });

    it('constructs new project', function() {
        let project = randar.project();
        assert.equal(project.directory().toString(), '.');
        assert.equal(project.onDisk, false);
    });

    it('saves', function() {
        let project = randar.project();
        project.directory(tmpDir);
        assert.equal(project.onDisk, false);

        let bin = project.newBin('Primary bin');
        assert.equal(Object.keys(project.bins).length, 1);
        assert.equal(Object.keys(project.folders).length, 1);

        let item = project.newItem(bin, 'geometry', 'Test Geometry');
        assert.equal(Object.keys(project.items).length, 1);

        let geo = item.object();
        for (let i = 0; i < 3; i++) {
            geo.append(randar.vertex(0.3, 0.2, 0.1));
        }

        project.save();
        assert.equal(project.onDisk, true);
    });

    it('loads', function() {
        let project = randar.project(tmpDir);
        assert.equal(project.onDisk, true);
        assert.equal(project.directory().toString(), tmpDir.toString());

        assert.equal(Object.keys(project.bins).length, 1);
        assert.equal(Object.keys(project.folders).length, 1);
        assert.equal(Object.keys(project.items).length, 1);

        let geo = project.items[0].object();
        assert.equal(geo.vertices.count(), 1);
        assert.equal(geo.indices.count(), 3);
    });
});
