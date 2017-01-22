#ifndef RANDAR_RENDER_FRAMEBUFFER_HPP
#define RANDAR_RENDER_FRAMEBUFFER_HPP

#include <randar/Render/Camera.hpp>
#include <randar/Render/Renderbuffer.hpp>
#include <randar/Render/Texture.hpp>

namespace randar
{
    /**
     * A framebuffer.
     *
     * Hard-coded to always use a texture. May be changed if it causes a huge
     * performance drop.
     *
     * May optionally include a depth buffer.
     */
    class Framebuffer : virtual public GpuResource
    {
    protected:
        bool depthBufferEnabled;

    public:
        Texture texture;
        Renderbuffer depthBuffer;
        Camera camera;

        /**
         * Constructor.
         */
        Framebuffer(
            std::string textureType = "rgba",
            bool enableDepthBuffer = false,
            unsigned int width = 1,
            unsigned int height = 1);

        /**
         * Checks whether a depth buffer is enabled.
         */
        bool hasDepthBuffer() const;

        /**
         * Resizes this framebuffer and its dependencies.
         */
        void resize(unsigned int width, unsigned int height);

        /**
         * Resource initialization and destruction.
         */
        virtual void initialize() override;
        virtual void destroy() override;
    };
}

#endif
