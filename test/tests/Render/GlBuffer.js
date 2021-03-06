const bufferTypes = {
    FloatArrayBuffer: [0.65, 0.78, 42.09, 654],
    IndexBuffer: [1, 8, 16, 32]
}

describe('GlBuffer', function() {
    for (bufferName in bufferTypes) {

        describe(bufferName, function() {
            let buffer;
            let data;

            beforeEach(function() {
                buffer = new randar[bufferName]();
                data = bufferTypes[bufferName];
            });

            it('constructs empty, uninitialized, and unsynced', function() {
                assert(!buffer.isInitialized())
                assert(!buffer.isSynced())

                assert.equal(buffer.count(), 0)
                assert(!buffer.isInitialized())
                assert(!buffer.isSynced())
            })

            it('is not automatically initialized after appending', function() {
                for (d of data) {
                    buffer.append(d)
                }

                assert.equal(buffer.count(), data.length)
                assert(!buffer.isInitialized())
                assert(!buffer.isSynced())
            })

            it('initializes with no data', function() {
                buffer.initialize()
                assert.equal(buffer.count(), 0)
                assert(buffer.isInitialized())
                assert(buffer.isSynced())
            })

            it('initializes with data', function() {
                for (d of data) {
                    buffer.append(d)
                }

                buffer.initialize()
                assert.equal(buffer.count(), data.length)
                assert(buffer.isInitialized())
                assert(buffer.isSynced())
            })

            it('syncs with no data', function() {
                buffer.sync()
                assert.equal(buffer.count(), 0)
                assert(buffer.isInitialized())
                assert(buffer.isSynced())
            })

            it('syncs with data', function() {
                for (d of data) {
                    buffer.append(d)
                }

                buffer.sync()
                assert.equal(buffer.count(), data.length)
                assert(buffer.isInitialized())
                assert(buffer.isSynced())
            })

            it('is synced accurately', function() {
                for (d of data) {
                    buffer.append(d)
                }

                buffer.sync()
                for (let i = 0; i < data.length; i++) {
                    assert.equal(buffer.get(i).toFixed(2), data[i].toFixed(2))
                    assert.equal(buffer.query(i).toFixed(2), data[i].toFixed(2))
                }
            })
        })
    }
})
