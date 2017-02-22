#include <randar/Ui/WindowListener.hpp>

// A global list of registered listeners.
std::set<randar::WindowListener*> randar::WindowListener::list;

// Constructor.
randar::WindowListener::WindowListener(::GLFWwindow& initWindow)
: window(initWindow)
{
    randar::WindowListener::list.insert(this);
}

// Destructor.
randar::WindowListener::~WindowListener()
{
    if (!randar::WindowListener::list.erase(this)) {
        throw std::logic_error("Corrupted window listener list");
    }
}

// Handles a window being resized.
void randar::WindowListener::onResize(uint32_t width, uint32_t height)
{

}

// Handles a native mouse movement.
void randar::WindowListener::onNativeMousePosition(double x, double y)
{
    if (this->leftButtonPressed) {
        this->leftButtonDragging = true;

        this->onLeftDrag(
            Vector(
                x - this->mousePosition.x,
                y - this->mousePosition.y
            ),  

            this->mouseModifiers
        );  
    }   

    this->mousePosition.x = x;
    this->mousePosition.y = y;

    this->onMouseMove(this->mousePosition);
}

// Handles a native mouse button event.
void randar::WindowListener::onNativeMouseButton(int button, int action, int mods)
{
    this->mouseModifiers.set(mods);

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

// Handles a native scroll event.
void randar::WindowListener::onNativeScroll(double x, double y)
{
    this->onScroll(Vector(x, y));
}

// Handles an artificial mouse movement event.
void randar::WindowListener::onMouseMove(const randar::MousePosition& position)
{

}

// Handles an artificial left click.
void randar::WindowListener::onLeftClick(const randar::MousePosition& position)
{

}

// Handles an artificial left mouse button drag.
void randar::WindowListener::onLeftDrag(const randar::Vector& drag, const randar::MouseModifiers& modifiers)
{

}

// Handles an artificial scroll event.
void randar::WindowListener::onScroll(const randar::Vector& scroll)
{

}
