#include <randar/Randar.hpp>
#include <randar/Ui/Ui.hpp>

int main()
{
    randar::seedRandomWithTime();
    randar::Ui ui;

    auto gpu = randar::getDefaultGpu();
    auto window = &gpu.getWindow();
    auto framebuffer = gpu.getDefaultFramebuffer();
    framebuffer.camera.setOrtho(true);

    while (true) {
        ::glfwPollEvents();
        ui.update(randar::getDefaultGpu());

        for (GLenum err; (err = glGetError()) != GL_NO_ERROR;) {
            throw std::runtime_error("Uncaught OpenGL error: " + std::to_string(err));
        }

        if (::glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS || ::glfwWindowShouldClose(window) != 0) {
            break;
        }

        gpu.bindTexture(ui.getTexture());

        ::glfwSwapBuffers(window);
    }
    return 0;
}
