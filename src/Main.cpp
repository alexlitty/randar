#include <randar/Randar.hpp>
#include <randar/Ui/Ui.hpp>

int main()
{
    randar::seedRandomWithTime();

    randar::Gpu& gpu = randar::getDefaultGpu();
    auto window = &gpu.getWindow();
    randar::Framebuffer& framebuffer = gpu.getDefaultFramebuffer();
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

    while (true) {
        gpu.check();
        ::glfwPollEvents();

        for (GLenum err; (err = glGetError()) != GL_NO_ERROR;) {
            throw std::runtime_error("Uncaught OpenGL error: " + std::to_string(err));
        }

        if (::glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS || ::glfwWindowShouldClose(window) != 0) {
            break;
        }

        gpu.clear(framebuffer, randar::Color(0.03f, 0.03f, 0.03f, 0.0f));
        ui.draw(randar::getDefaultGpu());
        ::glfwSwapBuffers(window);
    }
    return 0;
}
