#include <regex>
#include <randar/Ui/Ui.hpp>

// Constructor.
randar::Ui::Ui(randar::Browser& initBrowser)
: gpu(randar::getDefaultGpu()),
  window(&gpu.getWindow()),
  browser(initBrowser)
{
    this->project.load("./test-project/");
    this->project.save();
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

    // Import a new resource from a file.
    else if (name == "importResource") {
        const char* fileResult = ::tinyfd_openFileDialog(
            "Import Resource",
            this->project.getDirectory().c_str(),
            0,
            nullptr,
            nullptr,
            0
        );

        // No file was selected.
        if (!fileResult) {
            return;
        }

        returnValue = ::CefV8Value::CreateObject(
            ::CefRefPtr<::CefV8Accessor>(),
            ::CefRefPtr<::CefV8Interceptor>()
        );

        std::string file(fileResult);
        std::string extension = randar::getFileExtension(file);
        if (extension == "iqm") {
            //this->importer

            returnValue->SetValue(
                "message",
                ::CefV8Value::CreateString("Success!"),
                ::V8_PROPERTY_ATTRIBUTE_NONE
            );
        }
        
        else {
            returnValue->SetValue(
                "message",
                ::CefV8Value::CreateString("File not compatible."),
                ::V8_PROPERTY_ATTRIBUTE_NONE
            );
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
        this->monitor.draw();
        ::glfwSwapBuffers(this->window);
    }
}

// Runs through the browser and GLFW message loops.
void randar::Ui::runMessageLoops()
{
    ::glfwPollEvents();
    this->browser.update();
}
