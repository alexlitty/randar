#include <regex>
#include <randar/Ui/Ui.hpp>

// Constructor.
randar::Ui::Ui(randar::Browser& initBrowser)
: gpu(randar::getDefaultGpu()),
  window(&gpu.getWindow()),
  browser(initBrowser)
{
    ::glfwSetWindowUserPointer(this->window, this);
}

// Handles program log messages.
void randar::Ui::onLog(const randar::LogMessage& message)
{
    if (this->browser.isLoading()) {
        return;
    }

    this->browser.executeJs(
        "randar.onEngineLog(" + message.toJson().dump() + ")"
    );

    std::cout << message.toString() << std::endl;
}

// Handles left clicking.
void randar::Ui::onLeftClick(const randar::MousePosition& position)
{

}

// Handles dragging with the left mouse button.
void randar::Ui::onLeftDrag(const randar::Vector& drag, const randar::MouseModifiers& modifiers)
{
    if (this->monitor.targetModel) {
        if (modifiers.control) {
            glm::mat4 inverse = glm::inverse(this->monitor.camera.getViewMatrix());
            Vector movement = (drag / 100) * inverse;

            Quaternion quat(
                movement,
                movement.getMagnitude()
            );

            this->monitor.camera.move(quat);
        }
        
        else {
            Vector finalDrag = drag / 100;
            this->monitor.camera.pan(finalDrag.x, finalDrag.y);
        }
    }
}

// Handles mouse scrolling.
void randar::Ui::onScroll(const randar::Vector& scroll)
{

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
    else if (name == "setMonitorTarget") {
        if (arguments.size() >= 2 && arguments[0]->IsString() && arguments[1]->IsString()) {
            std::string category = arguments[0]->GetStringValue();
            std::string name = arguments[1]->GetStringValue();

            if (category == "models") {
                if (this->project.models.count(name)) {
                    this->monitor.setTarget(*this->project.models[name]);
                    return;
                }
            }
        }

        this->monitor.clearTarget();
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

        std::string file(fileResult);
        std::string extension = randar::getFileExtension(file);
        std::string message;

        // Import file.
        try {
            if (extension == "iqm") {
                this->importer.importIqm(file);
            }
            
            else {
                message = "File not compatible.";
            }
        }

        // Import failed.
        catch (std::runtime_error error) {
            message = error.what();
        }

        // Move new resources into project.
        for (auto item : this->importer.models) {
            std::string modelName = randar::insertUniqueKey(
                this->project.models,
                item.first,
                item.second
            );

            // Save to project directory.
            item.second->setFile(
                this->project.getDirectory()
                + "models/" + modelName + ".model"
            );
            item.second->save();
        }
        this->project.save();

        // Generate success message, unless the import failed.
        if (message == "") {
            message = "Imported "
                    + std::to_string(this->importer.models.size())
                    + " models";
        }
        this->importer.clear();

        // Return results.
        returnValue = ::CefV8Value::CreateObject(
            ::CefRefPtr<::CefV8Accessor>(),
            ::CefRefPtr<::CefV8Interceptor>()
        );

        returnValue->SetValue(
            "message",
            ::CefV8Value::CreateString(message),
            ::V8_PROPERTY_ATTRIBUTE_NONE
        );

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
    this->project.load("./test-project/");
    this->browser.executeJs("randar.ready();");
    
    // @todo - Test saving.
    this->project.save();

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
