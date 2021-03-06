#ifndef RANDAR_RENDER_GL_BUFFER_HPP
#define RANDAR_RENDER_GL_BUFFER_HPP

#include <randar/System/GraphicsContextResource.hpp>
#include <randar/System/GlNamedResource.hpp>

namespace randar
{
    /**
     * A templated OpenGL buffer.
     *
     * T is the buffer type, such as GL_ARRAY_BUFFER or GL_ELEMENT_ARRAY_BUFFER.
     * U is the type of data being stored in the buffer, such as GL_FLOAT.
     *
     * Typedefs of this template should always be used for improved SWIG
     * compatibility.
     */
    template <GLenum T, typename U>
    class GlBuffer :
        virtual public GraphicsContextResource,
        virtual public GlNamedResource
    {
    protected:
        /**
         * Local copy of the data that should be in the OpenGL buffer.
         *
         * Always available for simplicity and convenience. In the future, we
         * could intelligently free and re-allocate this data for memory
         * optimization.
         */
        std::vector<U> data;

        /**
         * Whether the local data is in-sync with the buffer data.
         *
         * Always false if the buffer is uninitialized.
         */
        bool inSync;

    public:
        /**
         * Constructors.
         */
        GlBuffer()
        : GlBuffer(randar::context())
        {

        }

        GlBuffer(GraphicsContext& context)
        : GraphicsContextResource(&context),
          inSync(false)
        {

        }

        /**
         * Assignment.
         */
        GlBuffer(const GlBuffer& other)
        : GraphicsContextResource(nullptr)
        {
            *this = other;
        }

        GlBuffer& operator =(const GlBuffer& other)
        {
            this->unassociateContext();
            if (other.ctx) {
                this->context(*other.ctx);
            }

            this->inSync = false;
            this->data = other.data;

            return *this;
        }

        /**
         * Destructor.
         *
         * Uninitializes the buffer if it is initialized.
         */
        ~GlBuffer()
        {
            this->unassociateContext();
        }

        /**
         * Initializes the buffer.
         *
         * Any local data available is immediately synced to the buffer.
         */
        using GraphicsContextResource::initialize;
        virtual void initialize() override
        {
            if (!this->ctx) {
                throw std::runtime_error("GlBuffer not assigned to a context");
            }

            if (!this->isInitialized()) {
                this->bindContext();

                ::glGenBuffers(1, &this->glName);
                this->ctx->check("Cannot generate OpenGL buffer");
                if (!this->glName) {
                    throw std::runtime_error("Failed to create OpenGL buffer");
                }
            }

            this->inSync = false;
            this->sync();
        };

        /**
         * Uninitializes the buffer.
         *
         * Nothing happens if the buffer is not initialized or the associated
         * graphics context is no longer available. Never throws an exception.
         */
        virtual void uninitialize() override
        {
            if (this->isInitialized()) {
                this->bindContext();

                ::glDeleteBuffers(1, &this->glName);
                this->glName = 0;

                this->inSync = false;
            }
        }

        /**
         * Whether this buffer is initialized.
         */
        bool isInitialized() const
        {
            return this->ctx && (this->glName > 0);
        }

        /**
         * Binds this buffer for further operations.
         *
         * Buffer is initialized if it isn't already.
         *
         * Throws an exception if the binding or automatic initialization fails.
         */
        void bind()
        {
            if (!this->isInitialized()) {
                this->initialize();
            }

            this->bindContext();
            ::glBindBuffer(T, this->glName);
        }

        /**
         * Syncs local data to the buffer.
         *
         * Nothing happens if no syncing is required. Throws an exception if
         * local data could not be synced.
         */
        void sync()
        {
            if (this->inSync) {
                return;
            }

            this->bind();
            ::glBufferData(T, this->data.size() * sizeof(U), this->data.data(), GL_STATIC_DRAW);
            this->ctx->check("Cannot write data to OpenGL buffer");

            this->inSync = true;
        }

        /**
         * Whether the local data is synced to the OpenGL buffer.
         */
        bool isSynced() const
        {
            return this->inSync;
        }

        /**
         * Clears the data in this buffer.
         */
        void clear()
        {
            this->data.clear();
            this->inSync = false;
        }

        /**
         * Sets the data for this buffer.
         *
         * Copies the given vector. In the future, we should allow adoption of
         * an existing array.
         */
        void set(std::vector<U>& newData)
        {
            this->data = newData;
            this->inSync = false;
        }

        /**
         * Appends a value to the buffer.
         */
        void append(U value)
        {
            this->data.push_back(value);
            this->inSync = false;
        }

        /**
         * Gets the local value at the specified index.
         *
         * Throws an exception if the index exceeds the buffer size.
         */
        U get(uint32_t index) const
        {
            if (index >= this->data.size()) {
                throw std::runtime_error("Accessing out-of-range GlBuffer index");
            }

            return this->data[index];
        }

        /**
         * Queries the OpenGL buffer value at the specified index.
         *
         * This should never be used outside debugging and testing; It is
         * extremely inefficient. The get method is superior in all practical
         * cases.
         *
         * Does not perform syncing prior to querying. Does not perform any
         * out-of-range checks.
         */
        U query(uint32_t index)
        {
            this->bind();

            U glData;
            ::glGetBufferSubData(T, index * sizeof(U), sizeof(U), &glData);
            this->ctx->check("Cannot query OpenGL buffer");
            return glData;
        }

        /**
         * Retrieves an immutable pointer to the local raw data.
         */
        const U* raw() const
        {
            return this->data.data();
        }

        /**
         * Counts the data available in this buffer.
         */
        uint32_t count() const
        {
            return this->data.size();
        }
    };

    typedef GlBuffer<GL_ARRAY_BUFFER, float> FloatArrayBuffer;
    typedef GlBuffer<GL_ARRAY_BUFFER, uint8_t> UCharArrayBuffer;
    typedef GlBuffer<GL_ARRAY_BUFFER, int16_t> ShortArrayBuffer;
    typedef GlBuffer<GL_ARRAY_BUFFER, uint16_t> UShortArrayBuffer;
    typedef GlBuffer<GL_ELEMENT_ARRAY_BUFFER, unsigned int> IndexBuffer;

    #ifdef SWIG
        %template(FloatArrayBuffer) GlBuffer<GL_ARRAY_BUFFER, float>;
        %template(UCharArrayBuffer) GlBuffer<GL_ARRAY_BUFFER, uint8_t>;
        %template(ShortArrayBuffer) GlBuffer<GL_ARRAY_BUFFER, int16_t>;
        %template(UShortArrayBuffer) GlBuffer<GL_ARRAY_BUFFER, uint16_t>;
        %template(IndexBuffer) GlBuffer<GL_ELEMENT_ARRAY_BUFFER, unsigned int>;
    #endif
}

#endif
