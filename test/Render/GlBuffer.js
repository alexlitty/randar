describe('GlBuffer', function() {
    describe.only('FloatArrayBuffer', function() {
        let ctx

        beforeEach(function() {
            ctx = new randar.GraphicsContext()
        })

        it('constructs empty, uninitialized, and unsynced', function() {
            let buffer = ctx.floatArrayBuffer()

            assert(!buffer.isInitialized())
            assert(!buffer.isSynced())

            assert.equal(buffer.count(), 0)
            assert(!buffer.isInitialized())
            assert(!buffer.isSynced())
        })

        it('is not automatically initialized after appending', function() {
            let buffer = ctx.floatArrayBuffer()
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
            let buffer = ctx.floatArrayBuffer()

            buffer.initialize()
            assert.equal(buffer.count(), 0)
            assert(buffer.isInitialized())
            assert(buffer.isSynced())
        })

        it('initializes with data', function() {
            let buffer = ctx.floatArrayBuffer()

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
            let buffer = ctx.floatArrayBuffer()

            buffer.sync()
            assert.equal(buffer.count(), 0)
            assert(buffer.isInitialized())
            assert(buffer.isSynced())
        })

        it('syncs with data', function() {
            let buffer = ctx.floatArrayBuffer()

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
})
