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
         * Initializes a GPU resource.
         *
         * Nothing happens if the resource is already initialized.
         */
        void initialize(GpuResource* resource);

        /**
         * Specializations for resource initializing.
         */
        void initialize(Framebuffer& framebuffer);
        void initialize(Shader& shader);
        void initialize(ShaderProgram& program);
        void initialize(Texture& texture);

        /**
         * Destroys a GPU resource.
         *
         * More accurately, the resource is destroyed on the GPU. The provided
         * object is not destroyed, and may be used to re-initialize the
         * resource later.
         *
         * Nothing happens if the resource is not initialized.
         */
        void destroy(GpuResource* resource);

        /**
         * Clears a GPU resource.
         */
        void clear(const Framebuffer& framebuffer, const Color& color);
        void clear(const Texture& texture);

        /**
         * Sets the underlying data of a GPU resource.
         */
        void setTextureData(const Texture& texture, const GLvoid* data);

        /**
         * Binds a GPU resource.
         *
         * These should only be called internally. Made public for easier
         * debugging.
         */
        void bind(const Framebuffer& framebuffer);
        void bind(const Mesh& mesh);
        void bind(const Texture& texture);
        void bind(const Vertices& vertices);

        /**
         * Drawing.
         */
        void draw(const Framebuffer& framebuffer, const Model& model);
    };

    /**
     * Retrieves the default GPU context.
     */
    Gpu& getDefaultGpu();
}

#endif
