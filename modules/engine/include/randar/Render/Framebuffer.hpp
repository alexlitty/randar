#ifndef RANDAR_RENDER_FRAMEBUFFER_HPP
#define RANDAR_RENDER_FRAMEBUFFER_HPP

#include <randar/Math/Dimensional2.hpp>
#include <randar/Render/Canvas.hpp>
#include <randar/Render/Renderbuffer.hpp>
#include <randar/Render/Texture.hpp>
#include <randar/System/Window.hpp>
#include <randar/Utility/Timer.hpp>

namespace randar
{
    class Geometry;
    class Model;

    /**
     * An OpenGL framebuffer.
     *
     * Framebuffers come in two flavors: Real off-screen framebuffers which
     * truly "are" customizable OpenGL framebuffers, and default on-screen
     * framebuffers which are constructed outside our program, associated with
     * a window, and represented with an instance of this class.
     *
     * Default framebuffers aren't customizable. You can't attach textures to
     * them and whatnot -- but you can otherwise render to them normally.
     *
     * We should spin-off default framebuffers as their own class when we have
     * the time.
     */
    class Framebuffer :
        virtual public GraphicsContextResource,
        virtual public GlNamedResource,
        virtual public Dimensional2<uint32_t>,
        virtual public Canvas
    {
        /**
         * Let windows construct default framebuffers.
         */
        friend randar::Window;

    public:
        /**
         * Help swig identify inherited items.
         */
        using Dimensional2<uint32_t>::getWidth;
        using Dimensional2<uint32_t>::getHeight;
        using Dimensional2<uint32_t>::setWidth;
        using Dimensional2<uint32_t>::setHeight;
        using Dimensional2<uint32_t>::hasDimensions;
        using Dimensional2<uint32_t>::isWithinDimensions;
        using GlNamedResource::getGlName;
        using Canvas::fps;
        using Canvas::camera;
        using Canvas::clear;
        using Canvas::draw;
        using Canvas::image;

    protected:
        bool isDefaultFramebuffer;
        Texture* texture;
        Renderbuffer* depthBuffer;

        /**
         * Window this framebuffer is associated with.
         *
         * If a window is present, this framebuffer is its default framebuffer.
         */
        randar::Window *window;

    public:
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

    protected:
        /**
         * Constructs a representation of a window's default framebuffer.
         *
         * Should only be invoked by a Randar window.
         */
        Framebuffer(randar::Window& initWindow);

    public:
        /**
         * Destructor.
         */
        virtual ~Framebuffer();

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
         * Resizes this framebuffer and its dependencies.
         */
        virtual void resize(uint32_t newWidth, uint32_t newHeight) override;

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

    protected:
        /**
         * Gets the framebuffer.
         *
         * Implemented for the Canvas class.
         */
        virtual Framebuffer& framebuffer() override;
    };
}

#endif
