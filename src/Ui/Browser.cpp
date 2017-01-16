#include <randar/Ui/Browser.hpp>

// Constructor.
randar::Browser::Browser()
{
    ::CefInitialize(
        ::CefMainArgs(),
        ::CefSettings(),
        ::CefRefPtr<::CefApp>(),
        nullptr
    );

    ::CefWindowInfo browserInfo;
    browserInfo.transparent_painting_enabled = true;
    browserInfo.SetAsChild(
        randar::getNativeWindow(randar::getDefaultWindow()),
        ::CefRect(0, 0, 800, 600)
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

// Retrieves the browser associated with this handler.
::CefRefPtr<::CefBrowser> randar::Browser::GetBrowser()
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
