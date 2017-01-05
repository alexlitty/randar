#include <randar/Randar.hpp>
#include <randar/Ui/Ui.hpp>

int main()
{
    randar::seedRandomWithTime();
    randar::Ui ui;

    randar::Gpu& gpu = randar::getDefaultGpu();
    auto window = &gpu.getWindow();
    randar::Framebuffer& framebuffer = gpu.getDefaultFramebuffer();
    //framebuffer.camera.setOrtho(true);
    framebuffer.camera.setPosition(randar::Vector(-5.0f, -5.0f, -2.0f));
    framebuffer.camera.setTarget(randar::Vector(0.0f, 0.0f, 0.0f));

    while (true) {
        gpu.check();
        ::glfwPollEvents();

        for (GLenum err; (err = glGetError()) != GL_NO_ERROR;) {
            throw std::runtime_error("Uncaught OpenGL error: " + std::to_string(err));
        }

        if (::glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS || ::glfwWindowShouldClose(window) != 0) {
            break;
        }

        gpu.clear(framebuffer, randar::Color(0.1f, 0.2f, 0.3f));
        ui.draw(randar::getDefaultGpu());
        ::glfwSwapBuffers(window);
    }
    return 0;
}
