#ifndef RANDAR_SYSTEM_WINDOW_HPP
#define RANDAR_SYSTEM_WINDOW_HPP

#include <memory>
#include <randar/Math/Dimensional2.hpp>
#include <randar/System/GraphicsContextResource.hpp>

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
      virtual public Dimensional2<uint32_t>
    {
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
             * The default framebuffer, provided for convenience.
             */
            std::unique_ptr<Framebuffer> fb;

        public:
            /**
             * Disable assignment.
             */
            Window(const Window& other) = delete;
            Window& operator =(const Window& other) = delete;

            /**
             * Constructor.
             */
            Window(GraphicsContext& context, uint32_t width, uint32_t height);

            /**
             * Destructor.
             */
            virtual ~Window();

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
            Framebuffer& framebuffer();

            /**
             * Presents the contents of the default framebuffer.
             *
             * This swaps the window's low-level back and front buffers -- not
             * to be confused with Randar's framebuffers. This is a platform
             * specific operation you needn't worry much about.
             *
             * Even though the low-level buffers are swapped, the contents of
             * the default framebuffer after this operation are undefined.
             */
            void present();
    };
}

#endif
