#ifndef RANDAR_ENGINE_GPU_HPP
#define RANDAR_ENGINE_GPU_HPP

#include <stdexcept>
#include <randar/Render.hpp>

namespace randar
{
    class Model;

    /**
     * An interface with a GPU driver.
     *
     * Each instance represents a context.
     */
    class Gpu
    {
    protected:
        Framebuffer defaultFramebuffer;
        ::GLuint boundFramebuffer;
        ::GLuint boundTexture;

        GLFWwindow *window;

    public:
        Gpu();
        ~Gpu();

        /**
         * Retrieves the default window.
         */
        ::GLFWwindow& getWindow();

        /**
         * Retrieves the default framebuffer.
         */
        const Framebuffer& getDefaultFramebuffer() const;
        Framebuffer& getDefaultFramebuffer();

        /**
         * Initializes a resource on the GPU.
         *
         * Nothing happens if the resource is already initialized.
         */
        void initialize(Framebuffer& framebuffer);
        void initialize(IndexBuffer& buffer);
        void initialize(Shader& shader);
        void initialize(ShaderProgram& program);
        void initialize(Texture& texture);
        void initialize(VertexArray& vertexArray);
        void initialize(VertexBuffer& buffer);

        /**
         * Destroys a resource on the GPU.
         *
         * Throws an error if the resource is not initialized yet.
         */
        void destroy(Framebuffer& framebuffer);
        void destroy(IndexBuffer& buffer);
        void destroy(Shader& shader);
        void destroy(ShaderProgram& program);
        void destroy(Texture& texture);
        void destroy(VertexArray& vertexArray);
        void destroy(VertexBuffer& buffer);

        /**
         * Clears a GPU resource.
         */
        void clear(const Framebuffer& framebuffer, const Color& color);
        void clear(const Texture& texture);

        /**
         * Writes the underlying data of a GPU resource.
         */
        void write(IndexBuffer& indexBuffer, const std::vector<unsigned int>& indices);
        void write(const Texture& texture, const GLvoid* data, GLenum dataFormat);
        void write(const VertexBuffer& buffer, const std::vector<Vertex>& vertices);

        /**
         * Binds a GPU resource.
         *
         * These should only be called internally. Made public for easier
         * debugging.
         */
        void bind(const Framebuffer& framebuffer);
        void bind(const IndexBuffer& buffer);
        void bind(const Model& model);
        void bind(const Texture& texture);
        void bind(const VertexBuffer& buffer);

        /**
         * Drawing.
         */
        void draw(
            const ShaderProgram &program,
            const Framebuffer& framebuffer,
            const Model& model);

        /**
         * Performs a sanity check.
         *
         * If the GPU is in a bad state, throws an error.
         */
        void check();
    };

    /**
     * Retrieves the default GPU context.
     */
    Gpu& getDefaultGpu();
}

#endif
