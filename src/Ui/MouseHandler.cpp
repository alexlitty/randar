#include <randar/Ui/MouseHandler.hpp>

// Handles a native mouse position change.
void randar::MouseHandler::onNativeMousePosition(double x, double y)
{
    if (this->leftButtonPressed) {
        this->leftButtonDragging = true;

        this->onLeftDrag(
            Vector(
                x - this->mousePosition.x,
                y - this->mousePosition.y
            )
        );
    }
}

// Handles a native mouse button event.
void randar::MouseHandler::onNativeMouseButton(int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        if (action == GLFW_PRESS) {
            this->leftButtonPressed = true;
        }

        else if (action == GLFW_RELEASE) {
            if (!this->leftButtonDragging) {
                this->onLeftClick(this->mousePosition);
            }

            this->leftButtonPressed = false;
            this->leftButtonDragging = false;
        }
    }
}

// Handles a native mouse scroll event.
void randar::MouseHandler::onNativeScroll(double x, double y)
{
    this->onScroll(Vector(x, y));
}

// Handles a left click from the mouse.
void randar::MouseHandler::onLeftClick(const randar::MousePosition& position)
{

}

// Handles dragging with the left mouse button.
void randar::MouseHandler::onLeftDrag(const randar::Vector& drag)
{

}

// Handles mouse scrolling.
void randar::MouseHandler::onScroll(const randar::Vector& scroll)
{

}
