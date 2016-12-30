#include <randar/Randar.hpp>

int main()
{
    randar::seedRandomWithTime();

    auto window = &randar::getDefaultGpu().getWindow();
    while (true) {
        ::glfwPollEvents();

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
