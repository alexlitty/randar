#include <randar/Engine/EngineMonitor.hpp>
#include <randar/Engine/Gpu.hpp>

randar::EngineMonitor::EngineMonitor()
: monitorFramebuffer("rgba", true)
{
    this->monitorFramebuffer.initialize();

    // Define shader program.
    this->program.vertexShader   = Shader(GL_VERTEX_SHADER, randar::readAsciiFile("./shaders/ui.vert"));
    this->program.fragmentShader = Shader(GL_FRAGMENT_SHADER, randar::readAsciiFile("./shaders/ui.frag"));
    this->program.initialize();

    // Monitor vertices.
    Vertex vertex;
    vertex.position.set(-0.5f, -1.0f, 0.001f);
    vertex.textureCoordinate.u = 0.0f;
    vertex.textureCoordinate.v = 1.0f;
    this->monitor.vertices.push_back(vertex);

    vertex.position.set(-0.5f, 1.0f, 0.001f);
    vertex.textureCoordinate.u = 0.0f;
    vertex.textureCoordinate.v = 0.0f;
    this->monitor.vertices.push_back(vertex);

    vertex.position.set(1.0f, -1.0f, 0.001f);
    vertex.textureCoordinate.u = 1.0f;
    vertex.textureCoordinate.v = 1.0f;
    this->monitor.vertices.push_back(vertex);

    vertex.position.set(1.0f, 1.0f, 0.001f);
    vertex.textureCoordinate.u = 1.0f;
    vertex.textureCoordinate.v = 0.0f;
    this->monitor.vertices.push_back(vertex);

    // Monitor face indices.
    this->monitor.faceIndices.push_back(0);
    this->monitor.faceIndices.push_back(1);
    this->monitor.faceIndices.push_back(2);

    this->monitor.faceIndices.push_back(3);
    this->monitor.faceIndices.push_back(1);
    this->monitor.faceIndices.push_back(2);

    // Send monitor model to the GPU.
    this->gpu.write(this->monitor);

    // Initialize the UI size.
    this->resize();
}

randar::EngineMonitor::~EngineMonitor()
{

}

// Resizes the UI to fit the default window.
void randar::EngineMonitor::resize()
{
    int width, height;
    ::glfwGetWindowSize(&this->gpu.getWindow(), &width, &height);

    this->defaultFramebuffer.camera.viewport = randar::Viewport(0, 0, width, height);

    this->monitorFramebuffer.resize(800, 600);
}

// Executes a Javascript method on the top-level "randar" object.
/*Awesomium::JSValue randar::EngineMonitor::jsExecute(const std::string& code, bool ignoreResult)
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

// Synchronizes the engine with the interface.
//void randar::EngineMonitor::sync()
//{
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
//}

// Draws the monitor.
void randar::EngineMonitor::draw()
{
    this->gpu.clear(this->defaultFramebuffer, Color(0.03f, 0.03f, 0.25f, 0.0f));

    this->gpu.bind(this->monitorFramebuffer.texture);
    this->gpu.draw(this->program, this->defaultFramebuffer, this->monitor);
}
