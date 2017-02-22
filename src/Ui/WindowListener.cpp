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
    MousePosition oldPosition = this->mousePosition;
    this->mousePosition.x = x;
    this->mousePosition.y = y;

    this->onMouseMove(oldPosition, this->mousePosition);
}

// Handles a native mouse button event.
void randar::WindowListener::onNativeMouseButton(int button, int action, int mods)
{
    this->mouseModifiers.set(mods);
    MouseButton randarButton;
    bool release;

    // Determine button type.
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        randarButton = MouseButton::LEFT;
    }
    
    else if (button == GLFW_MOUSE_BUTTON_RIGHT) {
        randarButton = MouseButton::RIGHT;
    }

    else {
        return;
    }

    // Determine release state.
    if (action == GLFW_PRESS) {
        release = false;
    }
    
    else if (action == GLFW_RELEASE) {
        release = true;
    }
    
    else {
        return;
    }

    // Send artificial event.
    this->onMouseButton(
        randarButton,
        this->mouseModifiers,
        this->mousePosition,
        release
    );
}

// Handles a native scroll event.
void randar::WindowListener::onNativeScroll(double x, double y)
{
    this->onScroll(Vector(x, y));
}
