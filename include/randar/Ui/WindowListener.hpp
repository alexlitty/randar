#ifndef RANDAR_UI_WINDOW_LISTENER_HPP
#define RANDAR_UI_WINDOW_LISTENER_HPP

#include <set>
#include <randar/Engine/Window.hpp>

namespace randar
{
    /**
     * An object that receives window events.
     *
     * Automatically registers itself for listening upon construction, and
     * removes itself from listening upon destruction.
     */
    struct WindowListener
    {
        /**
         * A global list of registered listeners.
         */
        static std::set<WindowListener*> list;

        /**
         * The window being listened to.
         */
        ::GLFWwindow& window;

        /**
         * Constructor.
         */
        WindowListener(::GLFWwindow& initWindow = randar::getDefaultWindow());

        /**
         * Destructor.
         */
        virtual ~WindowListener();

        /**
         * Triggers a resize event, based on the current size of the window.
         */
        void triggerResize();

        /**
         * Handles a window being resized.
         */
        virtual void onResize(uint32_t width, uint32_t height) = 0;
    };
}

#endif
