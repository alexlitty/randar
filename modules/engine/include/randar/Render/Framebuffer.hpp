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
    class Framebuffer :
        public GpuResource,
        virtual public Dimensional2<uint32_t>
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
         * Disabling copying.
         */
        Framebuffer(const Framebuffer& other) = delete;
        Framebuffer& operator=(const Framebuffer& other) = delete;

        /**
         * Constructs an off-screen framebuffer.
         *
         * Useless until a texture is attached.
         */
        Framebuffer(GraphicsContext& context);

        /**
         * Constructs a representation of a window's default framebuffer.
         */
        Framebuffer(randar::Window& initWindow);

        /**
         * Destructor.
         */
        ~Framebuffer();

        /**
         * Binds the framebuffer for further operations.
         */
        void bind();

    protected:
        /**
         * Current framebuffer completeness status.
         *
         * Used in the check method. Allocated here for performance.
         */
        GLenum status;

    public:
        /**
         * Checks the sanity of framebuffer attachments.
         *
         * Throws an exception if the framebuffer is not complete. Window
         * framebuffers never thrown an exception, as they are always ready
         * for use.
         */
        void check();

    protected:
        /**
         * Destroys this framebuffer and removes its attachments.
         */
        void destroy();

    public:
        /**
         * Resets all attachments.
         */
        void reset();

        /**
         * Attaches a texture to the framebuffer.
         *
         * Resets all prior attachments.
         *
         * Framebuffer is "resized" to attached texture size.
         */
        void attach(Texture& texture);

        /**
         * Clears the framebuffer with an optional color.
         */
        void clear(const Color& color = Color());

        /**
         * Resizes this framebuffer and its dependencies.
         */
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
    };
}

#endif
