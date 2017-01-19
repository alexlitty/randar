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
    // Get all project resources.
    if (name == "getResources") {
        returnValue = ::CefV8Value::CreateString(
            this->project.toJson().dump()
        );
    }

    // Switch the resource on the engine monitor.
    else if (name == "monitorResource" && arguments.size() >= 2) {
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
    this->browser.executeJs("randar.ready();");

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
