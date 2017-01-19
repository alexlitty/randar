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
    while (true) {
        gpu.check();

        // Run through message loops.
        ::glfwPollEvents();
        this->browser.update();

        // Let the browser load the HTML interface.
        if (this->browser.isLoading()) {
            continue;
        }

        // Draw and display the interface.
        monitor.draw();
        ::glfwSwapBuffers(this->window);
    }
}
