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
        void bind(const Framebuffer& framebuffer);
        ::GLuint boundFramebuffer;

        void bind(const Vertices& vertices);
        void bind(const Mesh& mesh);

        void bind(const Texture& texture);
        ::GLuint boundTexture;

        GLFWwindow *window;

    public:
        Gpu();
        ~Gpu();

        ::GLFWwindow& getWindow();

        /**
         * Framebuffers.
         */
        const Framebuffer& getDefaultFramebuffer() const;
        Framebuffer& getDefaultFramebuffer();

        void clear(const Framebuffer& framebuffer, const Color& color);

        /**
         * Texture manipulation.
         */
        void setTextureData(const Texture& texture, const GLvoid* data);
        void clear(const Texture& texture);

        /**
         * Initializes a GPU resource.
         *
         * If the GPU resource is already initialized, nothing happens.
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
         */
        void destroy(GpuResource* resource);

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
