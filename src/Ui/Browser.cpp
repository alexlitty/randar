#include <randar/Ui/Browser.hpp>

// Constructor.
randar::Browser::Browser()
: nativeCodeHandler(nullptr),
  screen(nullptr),
  texture(nullptr)
{

}

// Destructor.
randar::Browser::~Browser()
{
    ::CefShutdown();
}

// Tries to execute a CEF sub-process.
int randar::Browser::executeProcess(const ::CefMainArgs& mainArgs)
{
    ::CefRefPtr<Browser> app = this;
    int exitCode = ::CefExecuteProcess(mainArgs, app, nullptr);

    if (exitCode == -1) {
        // Run in single process mode for now. This is apparently meant for
        // debugging only, but it makes our application easier to set up.
        ::CefSettings settings;
        settings.single_process = true;

        ::CefInitialize(
            ::CefMainArgs(),
            settings,
            app,
            nullptr
        );

        int width, height;
        ::glfwGetWindowSize(&randar::getDefaultWindow(), &width, &height);

        this->texture = new Texture("rgba", width, height);
        this->texture->data.resize(width * height * 4);

        this->screen = new Model;
        Vertex vertex;

        vertex.position.set(-1.0f, -1.0f, 0.001f);
        vertex.textureCoordinate.u = 0.0f;
        vertex.textureCoordinate.v = 1.0f;
        this->screen->vertices.push_back(vertex);

        vertex.position.set(-1.0f, 1.0f, 0.001f);
        vertex.textureCoordinate.u = 0.0f;
        vertex.textureCoordinate.v = 0.0f;
        this->screen->vertices.push_back(vertex);

        vertex.position.set(1.0f, -1.0f, 0.001f);
        vertex.textureCoordinate.u = 1.0f;
        vertex.textureCoordinate.v = 1.0f;
        this->screen->vertices.push_back(vertex);

        vertex.position.set(1.0f, 1.0f, 0.001f);
        vertex.textureCoordinate.u = 1.0f;
        vertex.textureCoordinate.v = 0.0f;
        this->screen->vertices.push_back(vertex);

        this->screen->faceIndices.push_back(0);
        this->screen->faceIndices.push_back(1);
        this->screen->faceIndices.push_back(2);

        this->screen->faceIndices.push_back(3);
        this->screen->faceIndices.push_back(1);
        this->screen->faceIndices.push_back(2);

        randar::getDefaultGpu().write(*this->screen);

        ::CefWindowInfo browserInfo;
        browserInfo.SetAsWindowless(
            randar::getNativeWindow(randar::getDefaultWindow()),
            true
        );

        ::CefBrowserHost::CreateBrowser(
            browserInfo,
            this,
            ::CefString("file:///g/randar/bin/ui/ui.html"),
            ::CefBrowserSettings(),
            nullptr
        );
    }

    return exitCode;
}

// Checks whether the current page is loaded.
bool randar::Browser::isLoading()
{
    if (!this->browser) {
        return true;
    }
    return this->browser->IsLoading();
}

// Performs browser work and draws the engine monitor.
void randar::Browser::update()
{
    ::CefDoMessageLoopWork();
}

// Resizes the browser to fit a window.
void randar::Browser::resize(::GLFWwindow& window)
{
    int32_t width, height;
    ::glfwGetWindowSize(&window, &width, &height);

    if (width <= 0 || height <= 0) {
        throw std::domain_error(
            "Cannot resize browser to fit non-positive window dimensions"
        );
    }

    this->resize(static_cast<uint32_t>(width), static_cast<uint32_t>(height));
}

// Resizes the browser to specific dimensions.
void randar::Browser::resize(uint32_t width, uint32_t height)
{
    if (!this->browser) {
        throw std::logic_error("Cannot resize uninitialized browser");
    }

    if (!this->texture) {
        throw std::logic_error("Cannot resize browser with uninitialized texture");
    }

    this->texture->resize(width, height);
    this->texture->data.resize(width * height * 4);
    this->browser->GetHost()->WasResized();
}

// CefClient implementations.
::CefRefPtr<::CefDownloadHandler> randar::Browser::GetDownloadHandler()
{
    return this;
}

::CefRefPtr<::CefLifeSpanHandler> randar::Browser::GetLifeSpanHandler()
{
    return this;
}

::CefRefPtr<::CefLoadHandler> randar::Browser::GetLoadHandler()
{
    return this;
}

::CefRefPtr<::CefRenderHandler> randar::Browser::GetRenderHandler()
{
    return this;
}

::CefRefPtr<::CefRenderProcessHandler> randar::Browser::GetRenderProcessHandler()
{
    return this;
}

// CefDownload implementations.
void randar::Browser::OnBeforeDownload(
    ::CefRefPtr<::CefBrowser> browser,
    ::CefRefPtr<::CefDownloadItem> item,
    const ::CefString& name,
    ::CefRefPtr<::CefBeforeDownloadCallback> callback
) {
    callback->Continue(name, true);
}

// CefLifeSpan implementations.
void randar::Browser::OnAfterCreated(::CefRefPtr<::CefBrowser> browser)
{
    CEF_REQUIRE_UI_THREAD();
    AutoLock lock_scope(this);

    this->browser = browser;
    this->frame = this->browser->GetMainFrame();
    this->resize();

    CefLifeSpanHandler::OnAfterCreated(browser);
}

void randar::Browser::OnBeforeClose(::CefRefPtr<::CefBrowser> browser)
{
    CEF_REQUIRE_UI_THREAD();
    AutoLock lock_scope(this);

    browser = nullptr;
    //randar::StopBrowser(); @@@

    CefLifeSpanHandler::OnBeforeClose(browser);
}

// CefRenderHandler implementations.
bool randar::Browser::GetViewRect(
    ::CefRefPtr<::CefBrowser> browser,
    ::CefRect& rect)
{
    rect.x = 0;
    rect.y = 0;

    rect.width = this->texture->getWidth();
    rect.height = this->texture->getHeight();
    return true;
}

void randar::Browser::OnPaint(
    ::CefRefPtr<::CefBrowser> browser,
    ::CefRenderHandler::PaintElementType type,
    const ::CefRenderHandler::RectList& dirtyRects,
    const void* rawBuffer,
    int width,
    int height)
{
    const char* buffer = reinterpret_cast<const char*>(rawBuffer);

    for (auto rect : dirtyRects) {
        for (uint32_t row = rect.y; row < (rect.y + rect.height); row++) {
            for (uint32_t col = rect.x; col < (rect.x + rect.width); col++) {
                uint32_t start = (row * this->texture->getWidth() * 4);
                start += (col * 4);

                this->texture->data[start]     = buffer[start + 2];
                this->texture->data[start + 1] = buffer[start + 1];
                this->texture->data[start + 2] = buffer[start];
                this->texture->data[start + 3] = buffer[start + 3];
            }
        }
    }
    this->texture->write();
}

// CefRenderProcessHandler implementations.
void randar::Browser::OnContextCreated(
    ::CefRefPtr<::CefBrowser> browser,
    ::CefRefPtr<::CefFrame> frame,
    ::CefRefPtr<::CefV8Context> context)
{
    ::CefRefPtr<::CefV8Handler> handler = this;
    ::CefRefPtr<::CefV8Value> jsWindow = context->GetGlobal();

    jsWindow->SetValue(
        "setMonitorTarget",
        ::CefV8Value::CreateFunction("setMonitorTarget", handler),
        ::V8_PROPERTY_ATTRIBUTE_NONE
    );

    jsWindow->SetValue(
        "importResource",
        ::CefV8Value::CreateFunction("importResource", handler),
        ::V8_PROPERTY_ATTRIBUTE_NONE
    );

    jsWindow->SetValue(
        "setModelMeshTexture",
        ::CefV8Value::CreateFunction("setModelMeshTexture", handler),
        ::V8_PROPERTY_ATTRIBUTE_NONE
    );

    jsWindow->SetValue(
        "saveProject",
        ::CefV8Value::CreateFunction("saveProject", handler),
        ::V8_PROPERTY_ATTRIBUTE_NONE
    );

    jsWindow->SetValue(
        "createResource",
        ::CefV8Value::CreateFunction("createResource", handler),
        ::V8_PROPERTY_ATTRIBUTE_NONE
    );
}

// CefV8Handler implementations.
bool randar::Browser::Execute(
    const ::CefString& name,
    ::CefRefPtr<::CefV8Value> object,
    const ::CefV8ValueList& arguments,
    ::CefRefPtr<::CefV8Value>& returnValue,
    ::CefString& exception)
{
    if (this->nativeCodeHandler) {
        this->nativeCodeHandler->execute(name, arguments, returnValue);
        return true;
    }
    return false;
}

// Sets the handler for native code requests.
void randar::Browser::setNativeCodeHandler(randar::NativeCodeHandler* handler)
{
    this->nativeCodeHandler = handler;
}

// Handles messages between our main program and the CEF render process.
bool randar::Browser::OnProcessMessageReceived(
    ::CefRefPtr<::CefBrowser> browser,
    ::CefProcessId source,
    ::CefRefPtr<::CefProcessMessage> message)
{
    return false;
}

// Executes some JavaScript.
void randar::Browser::executeJs(const std::string& code)
{
    this->frame->ExecuteJavaScript(code, this->frame->GetURL(), 0);
}
