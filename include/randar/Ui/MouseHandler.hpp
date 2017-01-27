#ifndef RANDAR_UI_MOUSE_HANDLER_HPP
#define RANDAR_UI_MOUSE_HANDLER_HPP

#include <randar/Engine/Glfw.hpp>
#include <randar/Math/Vector.hpp>
#include <randar/Ui/MousePosition.hpp>

namespace randar
{
    class MouseHandler
    {
        MousePosition mousePosition;
        bool leftButtonPressed = false;
        bool leftButtonDragging = false;

    public:
        /**
         * Handlers for native mouse events.
         *
         * These are translated to events that are easier to consume by children
         * classes.
         */
        void onNativeMousePosition(double x, double y);
        void onNativeMouseButton(int button, int action, int mods);
        void onNativeScroll(double x, double y);

        /**
         * Mouse events that may be handled by children classes.
         */
        virtual void onLeftClick(const MousePosition& position);
        virtual void onLeftDrag(const Vector& drag);
        virtual void onScroll(const Vector& scroll);
    };
}

#endif
