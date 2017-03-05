#include <regex>
#include <randar/Ui/Ui.hpp>

// Constructor.
randar::Ui::Ui(randar::Browser& initBrowser)
: randar::WindowListener(randar::getDefaultGpu().getWindow()),
  gpu(randar::getDefaultGpu()),
  browser(initBrowser)
{
    ::glfwSetWindowUserPointer(&this->window, this);
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

// Handles cursor changes from the browser.
void randar::Ui::onCursorChange(randar::Cursor type)
{
    // @todo - Upgrade to the latest GLFW (>= 3.1) to set cursor information.
    // Once upgraded, we can uncomment the code below.

    /*static std::map<Cursor, GLFWcursor*> glfwCursors
    {
        { Cursor::NORMAL,  ::glfwCreateStandardCursor(GLFW_ARROW_CURSOR) },
        { Cursor::POINTER, ::glfwCreateStandardCursor(GLFW_HAND_CURSOR)  },
        { Cursor::TEXT,    ::glfwCreateStandardCursor(GLFW_IBEAM_CURSOR) }
    };

    ::glfwSetCursor(&this->window, glfwCursors[type]);*/
}

// Handles mouse movement events.
void randar::Ui::onMouseMove(
    const randar::MousePosition& oldPosition,
    const randar::MousePosition& position)
{
    ::CefMouseEvent event;
    event.x = position.x;
    event.y = position.y;

    this->browser.getHost()->SendMouseMoveEvent(event, false);
}

// Handles mouse button events.
void randar::Ui::onMouseButton(
    randar::MouseButton button,
    const randar::MouseModifiers& modifiers,
    const randar::MousePosition& position,
    bool release)
{
    ::CefMouseEvent event;
    event.x = position.x;
    event.y = position.y;

    ::CefBrowserHost::MouseButtonType cefButton;
    if (button == MouseButton::LEFT) {
        cefButton = ::CefBrowserHost::MouseButtonType::MBT_LEFT;
    }

    else if (button == MouseButton::RIGHT) {
        cefButton = ::CefBrowserHost::MouseButtonType::MBT_RIGHT;
    }

    else {
        return;
    }

    this->browser.getHost()->SendMouseClickEvent(
        event,
        cefButton,
        release,
        1
    );
}

// Handles dragging with the left mouse button.
/*void randar::Ui::onLeftDrag(const randar::Vector& drag, const randar::MouseModifiers& modifiers)
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
}*/

// Handles mouse scrolling.
void randar::Ui::onScroll(const randar::Vector& scroll)
{

}

// Handles window resize events.
void randar::Ui::onResize(uint32_t width, uint32_t height)
{
    Framebuffer::getDefault().resize(width, height);
    this->monitor.resize(width, height);
    this->browser.resize(width, height);
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
    if (name == "closeRandar") {
        this->close = true;
    }

    // Switch the resource on the engine monitor.
    else if (name == "setMonitorTarget") {
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

        this->importQueue.push_back(File(fileResult));
    }

    // Updates a resource.
    else if (name == "patchResource") {
        if (arguments.size() >= 3) {
            this->resourcePatches.emplace_back(
                arguments[0]->GetStringValue(),
                std::stoi(static_cast<std::string>(
                    arguments[1]->GetStringValue())),
                Json::parse(static_cast<std::string>(
                    arguments[2]->GetStringValue()))
            );
        }
    }

    // Set a model's mesh texture.
    else if (name == "setModelMeshTexture") {
        if (arguments.size() >= 0) {
            std::string stringModelId = arguments[0]->GetStringValue();
            uint32_t slotId = arguments[1]->GetIntValue();
            std::string stringTextureId = arguments[2]->GetStringValue();

            uint32_t modelId = std::stoi(stringModelId);
            uint32_t textureId = std::stoi(stringTextureId);

            Model *model = this->project.resources.getModel(modelId);
            model->setMeshTexture(
                slotId,
                this->project.resources.getTexture(textureId)
            );
        }
    }

    // Save the project.
    else if (name == "saveProject") {
        this->save = true;
    }

    // Create a new resource.
    else if (name == "createResource") {
        if (arguments.size() >= 1) {
            std::string category = arguments[0]->GetStringValue();

            if (category == "scenes") {
                this->createResourceQueue.push_back(category);
            }
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
    try {
        this->project.load(Directory("./test-project/"));
    }

    catch (const std::runtime_error& ex) {
        randar::logError(ex.what());
    }

    this->sync();
    this->browser.executeJs("randar.ready();");
    
    // Run the interface program.
    Framebuffer &defaultFramebuffer = Framebuffer::getDefault();
    while (true) {
        if (this->close) {
            break;
        }

        this->gpu.check();
        this->runMessageLoops();

        // Save the project.
        if (this->save) {
            this->project.save();
            this->save = false;
        }

        // Handle new resource importing.
        if (!this->importQueue.empty()) {
            for (auto file : this->importQueue) {
                std::string extension = file.getExtension();

                try {
                    if (extension == "iqm") {
                        this->project.resources.importIqm(file);
                    }

                    else if (extension == "png") {
                        this->project.resources.importPng(file);
                    }
                }

                catch (...) {
                    // @@@
                }
            }

            this->importQueue.clear();
            this->unsync();
        }

        // Handle new resource creation.
        if (!this->createResourceQueue.empty()) {
            for (auto category : this->createResourceQueue) {
                this->project.resources.addScene(new Scene);
            }

            this->createResourceQueue.clear();
            this->unsync();
        }
        this->sync();

        // Draw the interface.
        defaultFramebuffer.clear(Color(0.21f, 0.05f, 0.30f));
        ScopeLock monitorLock(this->monitor);
        this->monitor.draw();

        // Draw the engine monitor.
        this->gpu.bind(*this->browser.texture);
        this->gpu.draw(this->monitor.screenProgram, defaultFramebuffer, *this->browser.screen);

        ::glfwSwapBuffers(&this->window);
    }
}

// Runs through the browser and GLFW message loops.
void randar::Ui::runMessageLoops()
{
    ::glfwPollEvents();
    this->browser.update();
}
