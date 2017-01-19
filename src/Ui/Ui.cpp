#include <randar/Ui/Ui.hpp>

// Constructor.
randar::Ui::Ui(randar::Browser& initBrowser)
: gpu(randar::getDefaultGpu()),
  window(&gpu.getWindow()),
  browser(initBrowser)
{
    this->project.load("./test-project/");
}

// Handles interface function calls for engine interaction.
void randar::Ui::execute(
    const std::string& name,
    const ::CefV8ValueList& arguments,
    ::CefRefPtr<::CefV8Value>& returnValue)
{
    // Switch the resource on the engine monitor.
    if (name == "monitorResource" && arguments.size() >= 2) {
        ::CefRefPtr<::CefV8Value> category = arguments[0];
        ::CefRefPtr<::CefV8Value> name = arguments[1];

        if (category->IsString() && name->IsString()) {
            std::string realName = name->GetStringValue();
        }
    }
}

// Runs a single tick on the interface program.
void randar::Ui::run()
{
    // Wait for the browser to load the HTML interface.
    while (this->browser.isLoading()) {
        this->runMessageLoops();
    }

    // Initialize the interface.
    this->browser.setNativeCodeHandler(this);
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

// Handles requests made from the interface to the engine.
void randar::Ui::handleRequests()
{
}
