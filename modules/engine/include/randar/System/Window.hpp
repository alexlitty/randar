#ifndef RANDAR_SYSTEM_WINDOW_HPP
#define RANDAR_SYSTEM_WINDOW_HPP

#include <randar/Math/Dimensional2.hpp>
#include <randar/System/GraphicsContext.hpp>
#include <randar/Utility/Unassignable.hpp>

namespace randar
{
    /**
     * A window on the display.
     *
     * When a context is destroyed, its associated windows become meaningless.
     * Continuing to use such windows will result in undefined behavior. Thus,
     * be sure to destroy windows first.
     */
    class Window : public Dimensional2<uint32_t>, public Unassignable
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
             * Constructs a window from a graphics context.
             */
            Window(GraphicsContext& context, uint32_t width, uint32_t height);

            /**
             * Destructor.
             */
            ~Window();

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
             *
             * If no context is associated, an exception is thrown.
             */
            void use();
    };
}

#endif
