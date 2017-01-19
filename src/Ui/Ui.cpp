#include <randar/Ui/Ui.hpp>

// Constructor.
randar::Ui::Ui(randar::Browser& initBrowser)
: gpu(randar::getDefaultGpu()),
  window(&gpu.getWindow()),
  browser(initBrowser)
{
    this->project.load("./test-project/");
}

// Runs a single tick on the interface program.
void randar::Ui::execute()
{
    // Wait for the browser to load the HTML interface.
    while (this->browser.isLoading()) {
        this->runMessageLoops();
    }

    // Initialize the interface.
    this->sendResources();

    // Run the interface program.
    while (true) {
        gpu.check();
        this->runMessageLoops();

        // Draw and display the interface.
        monitor.draw();
        ::glfwSwapBuffers(this->window);
    }
}

// Runs through the browser and GLFW message loops.
void randar::Ui::runMessageLoops()
{
    ::glfwPollEvents();
    this->browser.update();
}

// Updates the resources available through the interface.
void randar::Ui::sendResources()
{
    this->browser.executeJs(
          std::string("randar.updateResources(")
        + this->project.toJson().dump()
        + std::string(");")
    );
}
