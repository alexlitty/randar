#include <randar/Ui/Browser.hpp>

// Constructor.
randar::Browser::Browser()
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
        ::CefInitialize(
            ::CefMainArgs(),
            ::CefSettings(),
            app,
            nullptr
        );

        ::CefWindowInfo browserInfo;
        browserInfo.transparent_painting_enabled = true;
        browserInfo.SetAsChild(
            randar::getNativeWindow(randar::getDefaultWindow()),
            ::CefRect(0, 0, 480, 1080)
        );  

        ::CefBrowserHost::CreateBrowser(
            browserInfo,
            this,
            ::CefString("file:///g/randar/bin/ui.html"),
            ::CefBrowserSettings(),
            nullptr
        );
    }

    return exitCode;
}

// Sets Randar engine information.
void randar::Browser::setEngineMonitor(randar::EngineMonitor* newMonitor)
{
    this->monitor = newMonitor;
}

// Performs browser work and draws the engine monitor.
void randar::Browser::update()
{
    ::CefDoMessageLoopWork();
    this->monitor->draw();
}

// CefClient implementations.
::CefRefPtr<::CefContextMenuHandler> randar::Browser::GetContextMenuHandler()
{
    return this;
}

::CefRefPtr<::CefDisplayHandler> randar::Browser::GetDisplayHandler()
{
    return this;
}

::CefRefPtr<::CefDownloadHandler> randar::Browser::GetDownloadHandler()
{
    return this;
}

::CefRefPtr<::CefDragHandler> randar::Browser::GetDragHandler()
{
    return this;
}

::CefRefPtr<::CefGeolocationHandler> randar::Browser::GetGeolocationHandler()
{
    return this;
}

::CefRefPtr<::CefKeyboardHandler> randar::Browser::GetKeyboardHandler()
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

::CefRefPtr<::CefRequestHandler> randar::Browser::GetRequestHandler()
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

// CefRenderProcessHandler implementations.
void randar::Browser::OnContextCreated(
    ::CefRefPtr<::CefBrowser> browser,
    ::CefRefPtr<::CefFrame> frame,
    ::CefRefPtr<::CefV8Context> context)
{
    ::CefRefPtr<::CefV8Value> window = context->GetGlobal();
    ::CefRefPtr<::CefV8Value> test = ::CefV8Value::CreateString("Testing!");
    window->SetValue("test", test, ::V8_PROPERTY_ATTRIBUTE_NONE);
}

// Handles messages between our main program and the CEF render process.
bool randar::Browser::OnProcessMessageReceived(
    ::CefRefPtr<::CefBrowser> browser,
    ::CefProcessId source,
    ::CefRefPtr<::CefProcessMessage> message)
{
    return false;
}
