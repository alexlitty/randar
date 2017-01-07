#include <randar/Randar.hpp>
#include <randar/Ui/Ui.hpp>

#include <iostream>
int main()
{
    randar::seedRandomWithTime();

    randar::Gpu& gpu = randar::getDefaultGpu();
    auto window = &gpu.getWindow();
    randar::Ui& ui = randar::getUi();

    ::glfwSetWindowSizeCallback(window, [](::GLFWwindow *window, int width, int height) {
        randar::getUi().resize();
    });

    ::glfwSetCursorPosCallback(window, [](::GLFWwindow *window, double x, double y) {
        randar::getUi().setMousePosition(
            static_cast<int>(x),
            static_cast<int>(y)
        );
    });

    ::glfwSetMouseButtonCallback(window, [](::GLFWwindow *window, int button, int action, int mods) {
        randar::MouseButton internalButton;
        switch (button) {
            case GLFW_MOUSE_BUTTON_LEFT:
                internalButton = randar::MouseButton::LEFT;
                break;

            case GLFW_MOUSE_BUTTON_MIDDLE:
                internalButton = randar::MouseButton::MIDDLE;
                break;

            case GLFW_MOUSE_BUTTON_RIGHT:
                internalButton = randar::MouseButton::RIGHT;
                break;

            default:
                return;
        }

        randar::Ui& ui = randar::getUi();
        if (action == GLFW_PRESS) {
            ui.pressMouse(internalButton);
        } else if (action == GLFW_RELEASE) {
            ui.releaseMouse(internalButton);
        }
    });

    while (true) {
        gpu.check();
        ::glfwPollEvents();

        for (GLenum err; (err = glGetError()) != GL_NO_ERROR;) {
            throw std::runtime_error("Uncaught OpenGL error: " + std::to_string(err));
        }

        if (::glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS || ::glfwWindowShouldClose(window) != 0) {
            break;
        }

        ui.draw();
        ::glfwSwapBuffers(window);
    }
    return 0;
}
