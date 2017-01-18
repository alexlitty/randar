#include <randar/Randar.hpp>
#include <randar/Ui/Browser.hpp>

#include <iostream>
int main(int argc, char *argv[])
{
    // CEF re-executes this process to perform its own needs. If this process
    // has been called by CEF, ::CefExecuteProcess() will handle what it needs.
    // Otherwise ::CefExecuteProcess() returns -1, indicating this is the main
    // Randar process.
    ::CefMainArgs mainArgs(argc, argv);
    ::CefRefPtr<randar::BrowserBridge> bridge = new randar::BrowserBridge();
    int exitCode = ::CefExecuteProcess(mainArgs, bridge, nullptr);
    if (exitCode != -1) {
        return exitCode;
    }

    randar::seedRandomWithTime();
    randar::Gpu& gpu = randar::getDefaultGpu();
    auto window = &gpu.getWindow();

    randar::EngineMonitor monitor;
    randar::Browser browser(monitor, bridge);

    // Run Randar with an interface.
    while (true) {
        ::glfwPollEvents();
        browser.update();

        // GPU sanity check.
        gpu.check();
        for (GLenum err; (err = glGetError()) != GL_NO_ERROR;) {
            throw std::runtime_error("Uncaught OpenGL error: " + std::to_string(err));
        }

        // Check for program exit.
        if (::glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS || ::glfwWindowShouldClose(window) != 0) {
            break;
        }

        ::glfwSwapBuffers(window);
    }
    return 0;
}
