#include <randar/Randar.hpp>
#include <randar/Ui/Browser.hpp>

#include <iostream>
int main(int argc, char *argv[])
{
    randar::Browser browser;

    // This process may be spawned by CEF for special browser processing. If
    // that is the case, this function will handle whatever CEF needs. Otherwise
    // the program continues.
    int exitCode = browser.executeProcess(::CefMainArgs(argc, argv));
    if (exitCode != -1) {
        return exitCode;
    }

    // Start Randar.
    randar::seedRandomWithTime();
    randar::Gpu& gpu = randar::getDefaultGpu();
    auto window = &gpu.getWindow();

    randar::EngineMonitor monitor;
    browser.setEngineMonitor(&monitor);

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
