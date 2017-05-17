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
         * Disable assignment.
         */
        GlBuffer(const GlBuffer& other) = delete;
        GlBuffer& operator =(const GlBuffer& other) = delete;

        /**
         * Constructor.
         *
         * Does not initialize the buffer. It will be initialized automatically
         * as necessary.
         */
        GlBuffer(GraphicsContext& context)
        : GraphicsContextResource(&context),
          inSync(false)
        {

        }

        /**
         * Destructor.
         *
         * Uninitializes the buffer if it is initialized.
         */
        ~GlBuffer()
        {
            this->uninitialize();
        }

        /**
         * Initializes the buffer.
         *
         * Any local data available is immediately synced to the buffer.
         *
         * Nothing happens if the buffer is already initialized. Throws an
         * exception if the buffer could not be initialized.
         */
        void initialize()
        {
            if (!this->isInitialized()) {
                ::glGenBuffers(1, &this->glName);

                this->ctx->check("Cannot generate OpenGL buffer");
                if (!this->glName) {
                    throw std::runtime_error("Failed to create OpenGL buffer");
                }

                this->sync();
            }
        };

        /**
         * Uninitializes the buffer.
         *
         * Nothing happens if the buffer is not initialized or the associated
         * graphics context is no longer available. Never throws an exception.
         */
        void uninitialize()
        {
            if (this->isInitialized()) {
                ::glDeleteBuffers(1, &this->glName);
                this->glName = 0;
            }
        }

        /**
         * Whether this buffer is initialized.
         */
        bool isInitialized() const
        {
            return this->ctx && this->glName;
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

            ::glBindBuffer(T, this->glName);
        }

        /**
         * Syncs local data to the buffer.
         *
         * Throws an exception if the data could not be synced.
         */
        void sync()
        {
            if (!this->inSync) {
                this->inSync = true;
            }

            this->bind();
            ::glBufferData(T, this->data.size() * sizeof(U), this->data.data(), GL_STATIC_DRAW);
            this->ctx->check("Cannot write data to OpenGL buffer");
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
         * Gets the value from the specified index.
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
    typedef GlBuffer<GL_ELEMENT_ARRAY_BUFFER, unsigned int> IndexBuffer;
}

#endif
