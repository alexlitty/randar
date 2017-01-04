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

    // Initialize resources on the GPU.
    this->initialize(randar::getDefaultGpu());
}

randar::Ui::~Ui()
{
    Awesomium::WebCore::Shutdown();
    this->destroy(randar::getDefaultGpu());
}

void randar::Ui::update(randar::Gpu& gpu)
{
    this->webCore->Update();

    if (!this->webView->IsLoading()) {
        this->surface = static_cast<Awesomium::BitmapSurface*>(this->webView->surface());

        unsigned char *buffer = new unsigned char[surface->width() * surface->height() * 4];
        this->surface->CopyTo(buffer, this->surface->width() * 4, 4, false, false);
        gpu.write(this->texture, buffer);

        delete[] buffer;
    }
}

// Resource initialization.
void randar::Ui::initialize(randar::Gpu& gpu)
{
    this->model.mesh.initialize(gpu);
    this->texture.initialize(gpu);
}

// Resource destruction.
void randar::Ui::destroy(randar::Gpu& gpu)
{
    this->model.mesh.destroy(gpu);
    this->texture.destroy(gpu);
}
