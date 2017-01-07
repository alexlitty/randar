#include <randar/Ui/Ui.hpp>
#include <randar/Engine/Gpu.hpp>

randar::Ui::Ui()
: webCore(Awesomium::WebCore::Initialize(Awesomium::WebConfig())),
  interfaceTexture(randar::Texture::RGBA),
  monitorFramebuffer(randar::Texture::RGBA, true)
{
    // Initialize Awesomium.
    this->webView = this->webCore->CreateWebView(
        1,
        1,
        nullptr,
        Awesomium::kWebViewType_Offscreen
    );

    Awesomium::WebString str = Awesomium::WebString::CreateFromUTF8("file:///g/randar/bin/ui.html", strlen("file:///g/randar/bin/ui.html"));
    Awesomium::WebURL url(str);
    this->webView->LoadURL(url);

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
}

randar::Ui::~Ui()
{
    Awesomium::WebCore::Shutdown();
    this->destroy();
}

void randar::Ui::resize()
{
    int width, height;

    ::glfwGetWindowSize(&this->gpu.getWindow(), &width, &height);

    this->defaultFramebuffer.camera.viewport = randar::Viewport(0, 0, width, height);
    this->webView->Resize(width, height);
    this->interfaceTexture.resize(width, height);

    this->monitorFramebuffer.resize(800, 600);
}

// Handles mouse movement.
void randar::Ui::setMousePosition(int x, int y)
{
    this->webView->InjectMouseMove(x, y);
}

// Handles mouse pressing.
void randar::Ui::pressMouse(randar::MouseButton button)
{
    this->webView->InjectMouseDown(randar::toAwesomium(button));
}

// Handles mouse releasing.
void randar::Ui::releaseMouse(randar::MouseButton button)
{
    this->webView->InjectMouseUp(randar::toAwesomium(button));
}

// Draws the UI.
void randar::Ui::draw()
{
    this->gpu.clear(this->defaultFramebuffer, Color(0.03f, 0.03f, 0.03f, 0.0f));
    this->webCore->Update();

    if (!this->webView->IsLoading()) {
        this->surface = static_cast<Awesomium::BitmapSurface*>(this->webView->surface());

        // View resizing is asynchronous. Wait for it to catch up.
        if (this->surface->width() != static_cast<int>(interfaceTexture.width)
            || this->surface->height() != static_cast<int>(interfaceTexture.height))
        {
            return;
        }

        unsigned char *buffer = new unsigned char[surface->width() * surface->height() * 4];
        this->surface->CopyTo(buffer, this->surface->width() * 4, 4, false, false);
        this->gpu.write(this->interfaceTexture, buffer, GL_BGRA);

        delete[] buffer;

        /**
         * Draw the current focus to monitor framebuffer.
         */
        this->gpu.clear(this->monitorFramebuffer, Color(0.0f, 0.0f, 0.0f));

        /**
         * Render interface.
         */
        this->gpu.bind(this->interfaceTexture);
        this->gpu.draw(this->program, this->defaultFramebuffer, this->interface);

        /**
         * Render monitor onto interface.
         */
        this->gpu.bind(this->monitorFramebuffer.texture);
        this->gpu.draw(this->program, this->defaultFramebuffer, this->monitor);
    }
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
