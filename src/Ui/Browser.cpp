#include <randar/Ui/Browser.hpp>

// Constructor.
randar::Browser::Browser(randar::EngineMonitor& initMonitor, ::CefRefPtr<randar::BrowserBridge> bridge)
: monitor(initMonitor)
{
    ::CefInitialize(
        ::CefMainArgs(),
        ::CefSettings(),
        bridge.get(),
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

// Destructor.
randar::Browser::~Browser()
{
    ::CefShutdown();
}

// Performs browser work and draws the engine monitor.
void randar::Browser::update()
{
    ::CefDoMessageLoopWork();
    this->monitor.draw();
}

// Retrieves the browser associated with this handler.
::CefRefPtr<::CefBrowser> randar::Browser::GetRawBrowser()
{
    return this->browser;
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

::CefRefPtr<::CefRenderProcessHandler> randar::BrowserBridge::GetRenderProcessHandler()
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

// @@ CefClient
bool randar::Browser::OnProcessMessageReceived(
    ::CefRefPtr<::CefBrowser> browser,
    ::CefProcessId source,
    ::CefRefPtr<::CefProcessMessage> message)
{
    std::cout << "received!!!" << std::endl;
    return false;
}

// Browser bridge.
bool randar::BrowserBridge::OnProcessMessageReceived(
    ::CefRefPtr<::CefBrowser> browser,
    ::CefProcessId source,
    ::CefRefPtr<::CefProcessMessage> message)
{
    //std::cout << "received!" << std::endl;
    return false;
}

void randar::BrowserBridge::OnContextCreated(
    ::CefRefPtr<::CefBrowser> browser,
    ::CefRefPtr<::CefFrame> frame,
    ::CefRefPtr<::CefV8Context> context)
{
    // Test.
    ::CefRefPtr<::CefProcessMessage> message = ::CefProcessMessage::Create("test_message");
    browser->SendProcessMessage(PID_BROWSER, message);

    //
    ::CefRefPtr<::CefV8Value> window = context->GetGlobal();
    ::CefRefPtr<::CefV8Value> test = ::CefV8Value::CreateString("Testing!");
    window->SetValue("test", test, ::V8_PROPERTY_ATTRIBUTE_NONE);
}
