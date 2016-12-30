#include <randar/Engine/Window.hpp>

::GLFWwindow& randar::getDefaultWindow()
{
    return randar::getDefaultGpu().getWindow();
}
