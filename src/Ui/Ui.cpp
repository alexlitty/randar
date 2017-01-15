#include <randar/Ui/Ui.hpp>
#include <randar/Engine/Gpu.hpp>

randar::Ui::Ui()
: cef(new randar::Cef),
  interfaceTexture("rgba", 1, 1),
  monitorFramebuffer("rgba", true)
{
    if (::CefExecuteProcess(::CefMainArgs(), this->cef.get(), nullptr) != -1) {
        throw std::runtime_error("Failed to execute browser process");
    }

    // Define shader program.
    this->program.vertexShader   = Shader(GL_VERTEX_SHADER, randar::readAsciiFile("./shaders/ui.vert"));
    this->program.fragmentShader = Shader(GL_FRAGMENT_SHADER, randar::readAsciiFile("./shaders/ui.frag"));

    // Initialize resources on the GPU.
    this->initialize();

    // Overlay vertices.
    std::vector<Vertex> vertices;
    Vertex vertex;
    vertex.color = Color(1.0f, 1.0f, 1.0f);

    vertex.position.set(-1.0f, -1.0f);
    vertex.textureCoordinate.u = 0.0f;
    vertex.textureCoordinate.v = 1.0f;
    vertices.push_back(vertex);

    vertex.position.set(-1.0f, 1.0f);
    vertex.textureCoordinate.u = 0.0f;
    vertex.textureCoordinate.v = 0.0f;
    vertices.push_back(vertex);

    vertex.position.set(1.0f, -1.0f);
    vertex.textureCoordinate.u = 1.0f;
    vertex.textureCoordinate.v = 1.0f;
    vertices.push_back(vertex);

    vertex.position.set(1.0f, 1.0f);
    vertex.textureCoordinate.u = 1.0f;
    vertex.textureCoordinate.v = 0.0f;
    vertices.push_back(vertex);

    // Overlay face indices.
    std::vector<unsigned int> indices;
    indices.push_back(0); indices.push_back(1); indices.push_back(2);
    indices.push_back(3); indices.push_back(1); indices.push_back(2);

    // Send overlay interface to GPU.
    this->gpu.write(this->interface.mesh.vertexBuffer, vertices);
    this->gpu.write(this->interface.mesh.indexBuffer, indices);

    // Monitor vertices.
    vertices.clear();
    vertex.position.set(-0.5f, -1.0f, -0.001f);
    vertex.textureCoordinate.u = 0.0f;
    vertex.textureCoordinate.v = 1.0f;
    vertices.push_back(vertex);

    vertex.position.set(-0.5f, 1.0f, -0.001f);
    vertex.textureCoordinate.u = 0.0f;
    vertex.textureCoordinate.v = 0.0f;
    vertices.push_back(vertex);

    vertex.position.set(1.0f, -1.0f, -0.001f);
    vertex.textureCoordinate.u = 1.0f;
    vertex.textureCoordinate.v = 1.0f;
    vertices.push_back(vertex);

    vertex.position.set(1.0f, 1.0f, -0.001f);
    vertex.textureCoordinate.u = 1.0f;
    vertex.textureCoordinate.v = 0.0f;
    vertices.push_back(vertex);

    // Send monitor model to the GPU.
    this->gpu.write(this->monitor.mesh.vertexBuffer, vertices);
    this->gpu.write(this->monitor.mesh.indexBuffer, indices);

    // Initialize the UI size.
    this->resize();

    this->project.load("./test-project/");
}

randar::Ui::~Ui()
{
    this->destroy();
}

// Resizes the UI to fit the default window.
void randar::Ui::resize()
{
    int width, height;

    ::glfwGetWindowSize(&this->gpu.getWindow(), &width, &height);

    this->defaultFramebuffer.camera.viewport = randar::Viewport(0, 0, width, height);
    this->interfaceTexture.resize(width, height);

    this->monitorFramebuffer.resize(800, 600);
}

// Executes a Javascript method on the top-level "randar" object.
/*Awesomium::JSValue randar::Ui::jsExecute(const std::string& code, bool ignoreResult)
{
    const char *str = code.c_str();

    // Execute async.
    if (ignoreResult) {
        this->webView->ExecuteJavascript(
            Awesomium::WSLit(str),
            Awesomium::WSLit("")
        );
        return Awesomium::JSValue::Undefined();
    }

    // Execute sync.
    Awesomium::JSValue result = this->webView->ExecuteJavascriptWithResult(
        Awesomium::WSLit(str),
        Awesomium::WSLit("")
    );

    // Sync results require a sanity check.
    this->check();
    return result;
}*/

// Handles mouse movement.
/*void randar::Ui::setMousePosition(int x, int y)
{
    this->webView->InjectMouseMove(x, y);
}

// Handles mouse pressing.
void randar::Ui::pressMouse(randar::MouseButton button)
{
}

// Handles mouse releasing.
void randar::Ui::releaseMouse(randar::MouseButton button)
{
}*/

// Handles keyboard input.
void randar::Ui::sendKey(int key)
{
}

// Synchronizes the engine with the interface.
void randar::Ui::sync()
{
    /*Awesomium::JSArray requests = this->jsExecute("randar.consumeSyncs();").ToArray();
    if (!requests.size()) {
        return;
    }

    for (unsigned int i = 0; i < requests.size(); i++) {
        Awesomium::JSValue value = requests[i];

        // Validate sync request.
        if (!value.IsObject()) {
            std::cout << "Ignoring non-object sync request" << std::endl;
            continue;
        }

        // Parse sync command.
        Awesomium::JSObject request = value.ToObject();
        std::string command = Awesomium::ToString(
            request.GetProperty(Awesomium::WSLit("command")).ToString()
        );

        // Feeds all resource information to the UI.
        if (command == "read") {
            this->jsExecute(std::string("randar.updateResources(")
                          + this->project.toJson().dump()
                          + std::string(");")
            );
        }

        // Unknown command.
        else {
            std::cout << "Ignoring unknown sync command '" << command << "'" << std::endl;
        }

        // Save after every interaction, temporarily for testing.
        if (!this->project.save()) {
            std::cout << "Project failed to save" << std::endl;
        }
    }*/
}

// Draws the UI.
void randar::Ui::draw()
{
    /*this->gpu.clear(this->defaultFramebuffer, Color(0.03f, 0.03f, 0.03f, 0.0f));

    // Keep the interface synchronized with the engine.
    this->sync();

    // Write the interface to a texture.
    unsigned char *buffer = new unsigned char[surface->width() * surface->height() * 4];
    this->surface->CopyTo(buffer, this->surface->width() * 4, 4, false, false);
    this->gpu.write(this->interfaceTexture, buffer, GL_BGRA);

    delete[] buffer;

    // Draw the current focus to the monitor framebuffer.
    this->gpu.clear(this->monitorFramebuffer, Color(0.0f, 0.0f, 0.0f));

    // Render the interface.
    this->gpu.bind(this->interfaceTexture);
    this->gpu.draw(this->program, this->defaultFramebuffer, this->interface);

    this->gpu.bind(this->monitorFramebuffer.texture);
    this->gpu.draw(this->program, this->defaultFramebuffer, this->monitor);*/
}

// Resource initialization.
void randar::Ui::initialize()
{
    this->program.initialize();
    this->interface.mesh.initialize();
    this->interfaceTexture.initialize();

    this->monitorFramebuffer.initialize();
    this->monitor.mesh.initialize();
}

// Resource destruction.
void randar::Ui::destroy()
{
    this->program.destroy();
    this->interface.mesh.destroy();
    this->interfaceTexture.destroy();
}

// Retrieves the primary UI instance.
randar::Ui& randar::getUi()
{
    static Ui ui;
    return ui;
}
