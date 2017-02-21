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

// Triggers a resize event, based on the current size of the window.
void randar::WindowListener::triggerResize()
{
    int32_t width, height;
    ::glfwGetWindowSize(&this->window, &width, &height);

    if (width <= 0 || height <= 0) {
        throw std::runtime_error(
            "Cannot handle window resize with non-positive dimensions"
        );
    }

    this->onResize(static_cast<uint32_t>(width), static_cast<uint32_t>(height));
}
