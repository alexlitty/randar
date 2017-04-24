#ifndef RANDAR_SYSTEM_WINDOW_HPP
#define RANDAR_SYSTEM_WINDOW_HPP

#include <randar/Math/Dimensional2.hpp>
#include <randar/System/GraphicsContext.hpp>

namespace randar
{
    /**
     * A window on the display.
     *
     * When a context is destroyed, its associated windows become meaningless.
     * Continuing to use such windows will result in undefined behavior. Thus,
     * be sure to destroy windows first.
     */
    class Window : virtual public Dimensional2<uint32_t>
    {
        protected:
            /**
             * Context this window is associated with.
             */
            GraphicsContext &ctx;

            /**
             * Raw window handle.
             */
            ::Window handle;
            
            /**
             * GLX's wrapper handle for the raw window.
             */
            ::GLXWindow glxWindow;

        public:
            /**
             * Disable assignment.
             */
            Window(const Window& other) = delete;
            Window& operator =(const Window& other) = delete;

            /**
             * Constructs a window from a graphics context.
             */
            Window(GraphicsContext& context, uint32_t width, uint32_t height);

            /**
             * Destructor.
             */
            ~Window();

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
             * Makes this window and its associated context current.
             */
            void use();

            /**
             * Swap the window's back and front buffers.
             */
            void swapBuffers();
    };
}

#endif
