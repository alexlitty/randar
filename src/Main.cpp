#include <randar/Ui/Ui.hpp>

int main(int argc, char *argv[])
{
    // Check basic platform requirements.
    if (CHAR_BIT != 8) {
        throw std::runtime_error(
            "Randar must be ran on a platform with 8-bit bytes."
        );
    }

    if (sizeof(float) != 4) {
        throw std::runtime_error(
            "Randar must be ran on a platform with 32-bit floats."
        );
    }

    // This process may be spawned by CEF for special browser processing. If
    // that is the case, this function will handle whatever CEF needs. Otherwise
    // the program continues.
    randar::Browser browser;
    int exitCode = browser.executeProcess(::CefMainArgs(argc, argv));
    if (exitCode != -1) {
        return exitCode;
    }

    // Prepare Randar as an interface.
    randar::seedRandomWithTime();
    randar::Ui ui(browser);

    // Register mouse movement handler.
    ::glfwSetCursorPosCallback(ui.window, [](::GLFWwindow* window, double x, double y) {
        reinterpret_cast<randar::Ui*>(
            ::glfwGetWindowUserPointer(window)
        )->onNativeMousePosition(x, y);
    });

    // Register mouse button handler.
    ::glfwSetMouseButtonCallback(ui.window, [](::GLFWwindow* window, int button, int action, int mods) {
        reinterpret_cast<randar::Ui*>(
            ::glfwGetWindowUserPointer(window)
        )->onNativeMouseButton(button, action, mods);
    });

    // Register mouse scroll handler.
    ::glfwSetScrollCallback(ui.window, [](::GLFWwindow* window, double x, double y) {
        reinterpret_cast<randar::Ui*>(
            ::glfwGetWindowUserPointer(window)
        )->onNativeScroll(x, y);
    });

    // Run Randar.
    ui.run();
    return 0;
}
