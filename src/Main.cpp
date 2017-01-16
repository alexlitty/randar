#include <randar/Randar.hpp>
#include <randar/Ui/Ui.hpp>

#include <iostream>
int main(int argc, char *argv[])
{
    ::CefMainArgs mainArgs(argc, argv);
    int exitCode = ::CefExecuteProcess(mainArgs, ::CefRefPtr<::CefApp>(), nullptr);
    if (exitCode != -1) {
        return exitCode;
    }

    ::CefInitialize(::CefMainArgs(), ::CefSettings(), ::CefRefPtr<::CefApp>(), nullptr);

    randar::seedRandomWithTime();

    randar::Gpu& gpu = randar::getDefaultGpu();
    auto window = &gpu.getWindow();
    randar::Ui& ui = randar::getUi();

    ::glfwSetWindowSizeCallback(window, [](::GLFWwindow *window, int width, int height) {
        //randar::getUi().resize();
    });

    ::glfwSetCursorPosCallback(window, [](::GLFWwindow *window, double x, double y) {
        /*randar::getUi().setMousePosition(
            static_cast<int>(x),
            static_cast<int>(y)
        );*/
    });

    ::glfwSetMouseButtonCallback(window, [](::GLFWwindow *window, int button, int action, int mods) {
        /*randar::Ui& ui = randar::getUi();
        if (action == GLFW_PRESS) {
            ui.pressMouse(internalButton);
        } else if (action == GLFW_RELEASE) {
            ui.releaseMouse(internalButton);
        }*/
    });

    ::glfwSetKeyCallback(window, [](::GLFWwindow *window, int key, int scancode, int action, int mods) {
        //randar::getUi().sendKey(key);
    });

    while (true) {
        gpu.check();
        ::glfwPollEvents();
        ui.draw();
        ::CefDoMessageLoopWork();

        for (GLenum err; (err = glGetError()) != GL_NO_ERROR;) {
            throw std::runtime_error("Uncaught OpenGL error: " + std::to_string(err));
        }

        if (::glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS || ::glfwWindowShouldClose(window) != 0) {
            break;
        }

        ::glfwSwapBuffers(window);
    }
    return 0;
}
