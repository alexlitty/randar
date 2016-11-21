#include <stdexcept>
#include <randar/Randar.hpp>

randar::Randar::Randar()
{
    // Initialize the monitor window.
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initalize glfw");
    }

    glfwWindowHint(GLFW_SAMPLES, 0);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    this->monitor = glfwCreateWindow(800, 600, "Randar Monitor", NULL, NULL);
    if (!this->monitor) {
        throw std::runtime_error("Failed to create glfw window");
    }

    glfwMakeContextCurrent(this->monitor);

    // Initialize GLEW.
    glewExperimental = true;
    if (glewInit() != GLEW_OK) {
        throw std::runtime_error("Failed to intialize GLEW");
    }

    // A single error seems to occur after initializing, might be a driver issue.
    // 
    // Investigate later.
    if (glGetError() != GL_NO_ERROR) {

    }
}

randar::Randar::~Randar()
{
    glfwDestroyWindow(this->monitor);
}

// Render the film.
void randar::Randar::run()
{
    try {
        Scene *currentScene = nullptr;
        while (!scenes.empty()) {
            glfwSwapBuffers(this->monitor);
            glfwPollEvents();

            // Listen for errors.
            for (GLenum err; (err = glGetError()) != GL_NO_ERROR;) {
                //throw std::runtime_error("OpenGL error: " + std::to_string(err));
            }

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

    catch (std::runtime_error *error) {
        std::cout << error->what() << std::endl;
    }
}
