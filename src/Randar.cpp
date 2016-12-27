#include <stdexcept>
#include <randar/Randar.hpp>

randar::Randar::Randar()
{
    Gpu& gpu = randar::getDefaultGpu();
    randar::seedRandomWithTime();
}

// Render the film.
void randar::Randar::run()
{
    try {
        Scene *currentScene = nullptr;
        while (!scenes.empty()) {
            ::glfwSwapBuffers(&randar::getDefaultWindow());
            ::glfwPollEvents();

            // Listen for errors.
            for (GLenum err; (err = glGetError()) != GL_NO_ERROR;) {
                throw std::runtime_error("OpenGL error: " + std::to_string(err));
            }

            // Received signal to stop.
            if (glfwGetKey(&randar::getDefaultWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS || ::glfwWindowShouldClose(&randar::getDefaultWindow()) != 0) {
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
