#include <randar/Ui/Ui.hpp>
#include <randar/Engine/Gpu.hpp>

randar::Ui::Ui()
: webCore(Awesomium::WebCore::Initialize(Awesomium::WebConfig())),
  texture(randar::Texture::RGBA, 1, 1)
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

    // Send overlay model to GPU.
    this->gpu.write(this->model.mesh.vertexBuffer, vertices);
    this->gpu.write(this->model.mesh.indexBuffer, indices);
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
    this->texture.width  = width;
    this->texture.height = height;
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

        if (this->surface->width() != static_cast<int>(texture.width)
            || this->surface->height() != static_cast<int>(texture.height))
        {
            return;
        }

        unsigned char *buffer = new unsigned char[surface->width() * surface->height() * 4];
        this->surface->CopyTo(buffer, this->surface->width() * 4, 4, false, false);
        this->gpu.write(this->texture, buffer, GL_BGRA);

        delete[] buffer;

        this->gpu.bind(this->texture);
        this->gpu.draw(this->program, this->defaultFramebuffer, this->model);
    }
}

// Resource initialization.
void randar::Ui::initialize()
{
    this->program.initialize();
    this->model.mesh.initialize();
    this->texture.initialize();
}

// Resource destruction.
void randar::Ui::destroy()
{
    this->program.destroy();
    this->model.mesh.destroy();
    this->texture.destroy();
}

// Retrieves the primary UI instance.
randar::Ui& randar::getUi()
{
    static Ui ui;
    return ui;
}
