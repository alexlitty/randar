#include <stdexcept>
#include <randar/randar.hpp>

randar::Randar::Randar()
{
    // Initialize the monitor window.
    if (!glfwInit()) {
        throw new std::runtime_error("Failed to initalize glfw");
    }

    glfwWindowHint(GLFW_SAMPLES, 0);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    this->monitor = glfwCreateWindow(800, 600, "Randar Monitor", NULL, NULL);
    if (!this->monitor) {
        throw new std::runtime_error("Failed to create glfw window");
    }

    glfwMakeContextCurrent(this->monitor);

    // Initialize GLEW.
    glewExperimental = true;
    if (glewInit() != GLEW_OK) {
        throw new std::runtime_error("Failed to intialize GLEW");
    }
}

randar::Randar::~Randar()
{
    glfwDestroyWindow(this->monitor);
}

// Render the film.
void randar::Randar::run()
{
    do {
        glfwSwapBuffers(this->monitor);
        glfwPollEvents();
    } while (
        glfwGetKey(this->monitor, GLFW_KEY_ESCAPE) != GLFW_PRESS
        && glfwWindowShouldClose(this->monitor) == 0
    );
}
