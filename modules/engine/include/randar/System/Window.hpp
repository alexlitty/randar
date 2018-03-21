#ifndef RANDAR_SYSTEM_WINDOW_HPP
#define RANDAR_SYSTEM_WINDOW_HPP

#include <memory>
#include <randar/Math/Dimensional2.hpp>
#include <randar/Render/Canvas.hpp>
#include <randar/System/GraphicsContextResource.hpp>
#include <randar/System/WindowOptions.hpp>

namespace randar
{
    class Framebuffer;

    /**
     * A window on the display.
     *
     * When a context is destroyed, its associated windows become meaningless.
     * Continuing to use such windows will result in undefined behavior. Thus,
     * be sure to destroy windows first.
     */
    class Window
    : virtual public GraphicsContextResource,
      virtual public Dimensional2<uint32_t>,
      virtual public Canvas
    {
    public:
        /**
         * Help swig identify inherited items.
         */
        using Canvas::camera;
        using Canvas::clear;
        using Canvas::draw;
        using Canvas::image;
        using Canvas::fps;
        using Canvas::camcorder;
    
    protected:
        /**
         * Raw window handle.
         */
        ::Window handle;
        
        /**
         * GLX's wrapper handle for the raw window.
         */
        ::GLXWindow glxWindow;

        /**
         * Default framebuffer.
         */
        std::unique_ptr<Framebuffer> fb;

    public:
        /**
         * Constructor, default context.
         */
        Window(
            uint32_t width,
            uint32_t height,
            const WindowOptions& options = WindowOptions()
        );

        /**
         * Constructor.
         */
        Window(
            GraphicsContext& context,
            uint32_t width,
            uint32_t height,
            const WindowOptions& options = WindowOptions()
        );

        /**
         * Disable assignment.
         */
        Window(const Window& other) = delete;
        Window& operator =(const Window& other) = delete;

        /**
         * Destructor.
         */
        virtual ~Window();

        /**
         * Whether the window is initialized and open.
         */
        bool isInitialized() const;

        /**
         * Closes the window.
         *
         * Once closed, a window may not be re-initialized again. A new
         * Window object must be created.
         */
        void close();

        /**
         * Checks if the window is still open.
         */
        bool isOpen();

        /**
         * Retrieves the associated context.
         */
        GraphicsContext& context();

        /**
         * Retrieves the native window handle.
         */
        ::Window native();

        /**
         * Retrieves the GLX window handle.
         */
        ::GLXWindow glx();

        /**
         * Binds the window for further operations.
         */
        void bind();

        /**
         * Retrieves an internal instance of the default framebuffer.
         */
        virtual Framebuffer& framebuffer() override;

        /**
         * Presents the contents of the default framebuffer.
         *
         * See Canvas::present.
         *
         * This swaps the window's back and front framebuffers. This is a
         * platform specific operation you needn't worry much about -- Just
         * make sure you call this to display renderings to the window.
         *
         * The swap isn't a true "swap." The contents of the default framebuffer
         * after this operation are undefined.
         */
        virtual void present() override;
    };
}

#endif
