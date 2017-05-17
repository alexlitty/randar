const bufferTypes = {
    FloatArrayBuffer: [0.65, 0.78, 42.09, 654],
    IndexBuffer: [1, 8, 16, 32]
}

describe('GlBuffer', function() {
    let ctx

    beforeEach(function() {
        ctx = new randar.GraphicsContext()
    })

    for (bufferName in bufferTypes) {
        let creatorName = bufferName[0].toLowerCase() + bufferName.slice(1)
        let buffer

        beforeEach(function() {
            buffer = ctx[creatorName]()
        })

        describe(bufferName, function() {
            it('constructs empty, uninitialized, and unsynced', function() {
                assert(!buffer.isInitialized())
                assert(!buffer.isSynced())

                assert.equal(buffer.count(), 0)
                assert(!buffer.isInitialized())
                assert(!buffer.isSynced())
            })

            it('is not automatically initialized after appending', function() {
                buffer.append(0.65)

                assert.equal(buffer.count(), 1)
                assert(!buffer.isInitialized())
                assert(!buffer.isSynced())

                buffer.append(0.78)
                buffer.append(0.01)
                buffer.append(1.00)

                assert.equal(buffer.count(), 4)
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
                buffer.append(0.09)
                assert.equal(buffer.count(), 1)
                assert(!buffer.isInitialized())
                assert(!buffer.isSynced())

                buffer.initialize()
                assert.equal(buffer.count(), 1)
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
                buffer.append(0.62)
                buffer.sync()

                assert.equal(buffer.count(), 1)
                assert(buffer.isInitialized())
                assert(buffer.isSynced())

                buffer.append(0.42)
                buffer.append(4.2)
                buffer.append(42.0)
                buffer.sync()

                assert.equal(buffer.count(), 4)
                assert(buffer.isInitialized())
                assert(buffer.isSynced())
            });
        })
    }
})
