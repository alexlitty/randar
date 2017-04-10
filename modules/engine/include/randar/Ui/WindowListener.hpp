#ifndef RANDAR_UI_WINDOW_LISTENER_HPP
#define RANDAR_UI_WINDOW_LISTENER_HPP

#include <set>
#include <randar/Engine/Window.hpp>
#include <randar/Ui/MouseButton.hpp>
#include <randar/Ui/MouseModifiers.hpp>
#include <randar/Ui/MousePosition.hpp>

namespace randar
{
    /**
     * An object that receives window events.
     *
     * Automatically registers itself for listening upon construction, and
     * removes itself from listening upon destruction.
     */
    class WindowListener
    {
        MouseModifiers mouseModifiers;
        MousePosition mousePosition;

    public:
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
         * Handles a window being resized.
         */
        virtual void onResize(uint32_t width, uint32_t height);

        /**
         * Handles native mouse events.
         *
         * These are used to create events that are easier to consume by
         * children classes, but these could be overriden if finer control is
         * desired.
         */
        virtual void onNativeMousePosition(double x, double y);
        virtual void onNativeMouseButton(int button, int action, int mods);
        virtual void onNativeScroll(double x, double y);

        /**
         * Handles artificial mouse events.
         *
         * These are formed from native mouse events. If the native handlers are
         * overriden, these will not be called automatically.
         */
        virtual void onMouseMove(
            const MousePosition& oldPosition,
            const MousePosition& position) = 0;

        virtual void onMouseButton(
            MouseButton button,
            const MouseModifiers& modifiers,
            const MousePosition& position,
            bool release) = 0;

        virtual void onScroll(const Vector& scroll) = 0;
    };
}

#endif
