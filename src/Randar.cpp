#include <stdexcept>
#include <randar/Randar.hpp>

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
    Scene *currentScene = nullptr;
    while (!scenes.empty()) {
        glfwSwapBuffers(this->monitor);
        glfwPollEvents();

        // Received signal to stop.
        if (glfwGetKey(this->monitor, GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwWindowShouldClose(this->monitor) != 0) {
            break;
        }

        // Initialize first or next scene.
        if (!currentScene) {
            currentScene = this->scenes.front();
            currentScene->initialize();
        }

        // Update scene, and move to the next one if completed.
        if (!currentScene->update()) {
            this->scenes.pop();
            currentScene = nullptr;
            continue;
        }

        currentScene->render();
    }
}
