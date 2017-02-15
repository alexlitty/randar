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
    ScopeLock monitorLock(this->monitor);

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

// Sends all project data to the interface.
void randar::Ui::sendAllData() {
    this->sendData(this->project.toJson());
}

// Sends all resources to the interface.
void randar::Ui::sendData(const Json& json)
{
    this->browser.executeJs("randar.receiveData(" + json.dump() + ");");
}

// Syncs data between the engine and interface, if necessary.
void randar::Ui::sync()
{
    if (!this->synced) {
        this->sendAllData();
        this->synced = true;
    }
}

// Indicate a need to sync the engine and interface data.
void randar::Ui::unsync()
{
    this->synced = false;
}

// Handles interface function calls for engine interaction.
void randar::Ui::execute(
    const std::string& name,
    const ::CefV8ValueList& arguments,
    ::CefRefPtr<::CefV8Value>& returnValue)
{
    // Switch the resource on the engine monitor.
    if (name == "setMonitorTarget") {
        ScopeLock monitorLock(this->monitor);

        if (arguments.size() >= 2 && arguments[0]->IsString() && arguments[1]->IsString()) {
            std::string category = arguments[0]->GetStringValue();
            std::string itemId   = arguments[1]->GetStringValue();

            uint32_t id = std::stoi(itemId);

            if (category == "models") {
                this->monitor.setTarget(
                    *this->project.resources.getModel(id)
                );
                return;
            }

            else if (category == "textures") {
                this->monitor.setTarget(
                    *this->project.resources.getTexture(id)
                );
                return;
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

        File file(fileResult);
        std::string extension = file.getExtension();
        std::string message;

        // Import file.
        try {
            if (extension == "iqm") {
                this->project.resources.importIqm(file);
            }

            else if (extension == "png") {
                this->project.resources.importPng(file);
            }
            
            else {
                message = "File not compatible.";
            }
        }

        // Import failed.
        catch (std::runtime_error error) {
            message = error.what();
        }

        // Generate success message, unless the import failed.
        if (message == "") {
            message = "Imported!";
        }

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

        this->unsync();
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
    try {
        this->project.load(Directory("./test-project/"));
        this->project.save();
    }

    catch (const std::runtime_error& ex) {
        randar::logError(ex.what());
    }

    this->sync();
    this->browser.executeJs("randar.ready();");
    
    // Run the interface program.
    Framebuffer defaultFramebuffer;
    while (true) {
        this->gpu.check();
        this->runMessageLoops();
        this->sync();

        // Draw and display the interface.
        ScopeLock monitorLock(this->monitor);

        defaultFramebuffer.clear(Color(0.15f, 0.15, 0.0f));
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
