#include <randar/Ui/Browser.hpp>

// Constructor.
randar::Browser::Browser()
: nativeCodeHandler(nullptr)
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
        this->texture = new Texture("rgba", 800, 600);
        this->texture->data.resize(800 * 600 * 4);

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
    this->browser->GetHost()->WasResized();
    this->frame = this->browser->GetMainFrame();

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
    rect.width = 800;
    rect.height = 600;
    return true;
}

void randar::Browser::OnPaint(
    ::CefRefPtr<::CefBrowser> browser,
    ::CefRenderHandler::PaintElementType type,
    const ::CefRenderHandler::RectList& dirtyRects,
    const void* buffer,
    int width,
    int height)
{
    std::cout << "painting" << std::endl;
    for (auto rect : dirtyRects) {
        for (uint32_t row = rect.y; row < (rect.y + rect.height); row++) {
            for (uint32_t col = rect.x; col < (rect.x + rect.width); col++) {
                uint32_t start = (row * this->texture->getWidth() * 4);
                start += (col * 4);

                for (uint8_t i = 0; i < 4; i++) {
                    this->texture->data[start + i] = reinterpret_cast<const char*>(buffer)[start + i];
                }
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
