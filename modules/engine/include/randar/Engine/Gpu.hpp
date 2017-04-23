#ifndef RANDAR_ENGINE_GPU_HPP
#define RANDAR_ENGINE_GPU_HPP

#include <stdexcept>
#include <GL/glew.h>
#include <GL/glx.h>
#include <randar/Math/Rect.hpp>
#include <randar/Render.hpp>
#include <randar/Render/Image.hpp>
#include <randar/Utility/glm.hpp>

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
        ::Display *display;
        ::GLXFBConfig *fbConfig;
        ::GLXPbuffer pbuffer;
        ::XVisualInfo *visualInfo;
        ::GLXContext context;

        Dimensional2<uint32_t> pbufferDimensions;

    public:
        Gpu();
        ~Gpu();

        /**
         * Makes the context of this GPU current.
         */
        void use();

        /**
         * Initializes a resource on the GPU.
         *
         * Nothing happens if the resource is already initialized.
         */
        void initialize(IndexBuffer& buffer);
        void initialize(Renderbuffer& renderbuffer);
        void initialize(Shader& shader);
        void initialize(ShaderProgram& program);
        void initialize(VertexArray& vertexArray);
        void initialize(VertexBuffer& buffer);

        /**
         * Destroys a resource on the GPU.
         *
         * Throws an error if the resource is not initialized yet.
         */
        void destroy(IndexBuffer& buffer);
        void destroy(Renderbuffer& renderbuffer);
        void destroy(Shader& shader);
        void destroy(ShaderProgram& program);
        void destroy(VertexArray& vertexArray);
        void destroy(VertexBuffer& buffer);

        /**
         * Resizes a GPU resource.
         */
        void resize(Renderbuffer& renderbuffer, unsigned int width, unsigned int height);

        /**
         * Writes the underlying data of a GPU resource.
         */
        void write(IndexBuffer& indexBuffer, const std::vector<uint32_t>& indices);
        void write(const Texture& texture);
        void write(const Texture& texture, const GLvoid* data, GLenum dataFormat);
        void write(const Texture& texture, const Rect<uint32_t>& rect, const GLvoid* data, GLenum dataFormat);
        void write(const VertexBuffer& buffer, const std::vector<Vertex>& vertices);
        void write(Model& model);

        /**
         * Gets the location of a shader program uniform.
         *
         * Returns -1 if the uniform is not used by the program.
         */
        ::GLint getUniformLocation(
            const ShaderProgram& program,
            const std::string& name);

        /**
         * Sets the value of a shader program uniform.
         *
         * Nothing happens if the uniform location is -1.
         */
        void setUniform(
            const ShaderProgram& program,
            ::GLint location,
            const glm::mat4& matrix);

        void setUniform(
            const ShaderProgram& program,
            ::GLint location,
            int integer);

        /**
         * Binds a GPU resource.
         *
         * These should only be called internally. Made public for easier
         * debugging.
         */
        void bind(const IndexBuffer& buffer);
        void bind(const Model& model);
        void bind(const Renderbuffer& renderbuffer);
        void bind(const VertexBuffer& buffer);

        /**
         * Drawing.
         */
        void draw(
            ShaderProgram &program,
            Framebuffer& framebuffer,
            Model& model);

        /**
         * Performs a sanity check.
         *
         * If the GPU is in a bad state, throws an error.
         */
        void check();

        /**
         * Waits until all commands have been processed by the GPU.
         */
        void finish();
    };
}

#endif
