#include <randar/Ui/Ui.hpp>
#include <randar/Engine/Gpu.hpp>

randar::Ui::Ui()
: webCore(Awesomium::WebCore::Initialize(Awesomium::WebConfig())),
  texture(randar::Texture::RGBA, 800, 600)
{
    // Initialize Awesomium.
    this->webView = this->webCore->CreateWebView(
        800,
        600,
        nullptr,
        Awesomium::kWebViewType_Offscreen
    );

    Awesomium::WebString str = Awesomium::WebString::CreateFromUTF8("http://www.google.com", strlen("http://www.google.com"));
    Awesomium::WebURL url(str);
    this->webView->LoadURL(url);

    // Define shader program.
    this->program.vertexShader   = Shader(GL_VERTEX_SHADER, randar::readAsciiFile("./shaders/ui.vert"));
    this->program.fragmentShader = Shader(GL_FRAGMENT_SHADER, randar::readAsciiFile("./shaders/ui.frag"));

    // Initialize resources on the GPU.
    this->initialize(randar::getDefaultGpu());

    // Overlay vertices.
    std::vector<Vertex> vertices;
    Vertex vertex;
    vertex.color = Color(75, 0, 150);

    vertex.position.set(0.0f, 0.0f);
    vertex.textureCoordinate.u = 0.0f;
    vertex.textureCoordinate.v = 0.0f;
    vertices.push_back(vertex);

    vertex.position.set(0.0f, 1.0f);
    vertex.textureCoordinate.u = 0.0f;
    vertex.textureCoordinate.v = 1.0f;
    vertices.push_back(vertex);

    vertex.position.set(1.0f, 0.0f);
    vertex.textureCoordinate.u = 1.0f;
    vertex.textureCoordinate.v = 0.0f;
    vertices.push_back(vertex);

    vertex.position.set(1.0f, 1.0f);
    vertex.textureCoordinate.u = 1.0f;
    vertex.textureCoordinate.v = 1.0f;
    vertices.push_back(vertex);

    // Overlay face indices.
    std::vector<unsigned int> indices;
    indices.push_back(0); indices.push_back(1); indices.push_back(2);
    indices.push_back(3); indices.push_back(1); indices.push_back(2);

    // Send overlay model to GPU.
    Gpu& gpu = randar::getDefaultGpu();
    gpu.write(this->model.mesh.vertexBuffer, vertices);
    gpu.write(this->model.mesh.indexBuffer, indices);
}

randar::Ui::~Ui()
{
    Awesomium::WebCore::Shutdown();
    this->destroy(randar::getDefaultGpu());
}

void randar::Ui::draw(randar::Gpu& gpu)
{
    this->webCore->Update();

    if (!this->webView->IsLoading()) {
        this->surface = static_cast<Awesomium::BitmapSurface*>(this->webView->surface());

        unsigned char *buffer = new unsigned char[surface->width() * surface->height() * 4];
        this->surface->CopyTo(buffer, this->surface->width() * 4, 4, false, false);
        gpu.write(this->texture, buffer);

        delete[] buffer;

        gpu.bind(this->texture);
        gpu.draw(this->program, gpu.getDefaultFramebuffer(), this->model);
    }
}

// Resource initialization.
void randar::Ui::initialize(randar::Gpu& gpu)
{
    this->program.initialize(gpu);
    this->model.mesh.initialize(gpu);
    this->texture.initialize(gpu);
}

// Resource destruction.
void randar::Ui::destroy(randar::Gpu& gpu)
{
    this->program.destroy(gpu);
    this->model.mesh.destroy(gpu);
    this->texture.destroy(gpu);
}
