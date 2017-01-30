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
        bool isDefaultFramebuffer;
        Texture* texture;
        Renderbuffer* depthBuffer;

    public:
        Camera camera;

        /**
         * Constructs a default framebuffer.
         *
         * The default framebuffer is created outside of Randar. This is simply
         * a representation of it.
         */
        Framebuffer();

        /**
         * Constructs and initializes new framebuffer.
         *
         * @todo - Throw exception if not initialized.
         */
        Framebuffer(
            std::string textureType,
            bool enableDepthBuffer = false,
            unsigned int width = 1,
            unsigned int height = 1);

        /**
         * Destructor.
         */
        ~Framebuffer();

        /**
         * Whether this is the default framebuffer.
         */
        bool isDefault() const;

        /**
         * Whether this framebuffer is initialized on the GPU.
         */
        virtual bool isInitialized() const override;

        /**
         * Resizes this framebuffer and its dependencies.
         */
        void resize(unsigned int width, unsigned int height);

        /**
         * Checks whether this framebuffer has a texture and depth buffer.
         */
        bool hasTexture() const;
        bool hasDepthBuffer() const;

        /**
         * Gets the texture and depth buffer.
         */
        Texture& getTexture();
        Renderbuffer& getDepthBuffer();
    };
}

#endif
