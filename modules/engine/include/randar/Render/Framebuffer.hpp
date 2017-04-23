#ifndef RANDAR_RENDER_FRAMEBUFFER_HPP
#define RANDAR_RENDER_FRAMEBUFFER_HPP

#include <randar/Math/Dimensional2.hpp>
#include <randar/Render/Camera.hpp>
#include <randar/Render/Image.hpp>
#include <randar/Render/Renderbuffer.hpp>
#include <randar/Render/Texture.hpp>
#include <randar/System/Window.hpp>

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
    class Framebuffer : virtual public GpuResource, public Dimensional2<uint32_t>
    {
    protected:
        bool isDefaultFramebuffer;
        Texture* texture;
        Renderbuffer* depthBuffer;

        /**
         * Window this framebuffer is associated with.
         *
         * If this is present, this is the default framebuffer for the window.
         */
        randar::Window *window;

    public:
        /**
         * Camera used to view this framebuffer.
         */
        Camera camera;

        /**
         * Constructs a representation of a window's default framebuffer.
         */
        Framebuffer(randar::Window& initWindow);

        /**
         * Constructs a new framebuffer.
         */
        /*Framebuffer(
            GraphicsContext& initCtx,
            std::string textureType,
            bool enableDepthBuffer = false,
            unsigned int initWidth = 1,
            unsigned int initHeight = 1);*/

        /**
         * Destructor.
         */
        ~Framebuffer();

        /**
         * Binds the framebuffer for further operations.
         */
        void bind();

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
         * Checks whether this framebuffer has a texture and depth buffer.
         */
        bool hasTexture() const;
        bool hasDepthBuffer() const;

        /**
         * Gets the texture and depth buffer.
         */
        Texture& getTexture();
        Renderbuffer& getDepthBuffer();

        /**
         * Reads the contents of the framebuffer.
         */
        void read(Image& image);
        Image read();
    };
}

#endif
