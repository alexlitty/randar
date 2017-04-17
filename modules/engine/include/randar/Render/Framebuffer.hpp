#ifndef RANDAR_RENDER_FRAMEBUFFER_HPP
#define RANDAR_RENDER_FRAMEBUFFER_HPP

#include <randar/Math/Dimensional2.hpp>
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

        uint32_t width;
        uint32_t height;

        /**
         * Constructs a default framebuffer.
         *
         * The actual framebuffer is created outside this class. This is simply
         * a representation of it.
         */
        Framebuffer(Gpu& gpuInit);

    public:
        friend Gpu;

        /**
         * Camera used to view this framebuffer.
         */
        Camera camera;

        /**
         * Constructs and initializes new framebuffer.
         *
         * @todo - Throw exception if not initialized.
         */
        Framebuffer(
            Gpu& gpuInit,
            std::string textureType,
            bool enableDepthBuffer = false,
            unsigned int initWidth = 1,
            unsigned int initHeight = 1);

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
         * Clears the framebuffer with an optional color.
         */
        void clear(const Color& color = Color());

        /**
         * Resizes this framebuffer and its dependencies.
         */
        void resize(Dimensional2<uint32_t> dimensions);
        void resize(uint32_t newWidth, uint32_t newHeight);

        /**
         * Gets the width and height of this framebuffer.
         */
        uint32_t getWidth() const;
        uint32_t getHeight() const;

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
