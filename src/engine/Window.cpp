#include <randar/engine/Window.hpp>

::GLFWwindow& randar::getDefaultWindow()
{
    return randar::getDefaultGpu().getWindow();
}
