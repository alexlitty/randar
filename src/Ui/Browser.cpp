#include <randar/Ui/Browser.hpp>

// Constructor.
randar::CefHandler::CefHandler()
{

}

// Destructor.
randar::CefHandler::~CefHandler()
{

}

// Retrieves the browser associated with this handler.
::CefRefPtr<::CefBrowser> randar::CefHandler::GetBrowser()
{
    return this->browser;
}

// CefClient implementations.
::CefRefPtr<::CefContextMenuHandler> randar::CefHandler::GetContextMenuHandler()
{
    return this;
}

::CefRefPtr<::CefDisplayHandler> randar::CefHandler::GetDisplayHandler()
{
    return this;
}

::CefRefPtr<::CefDownloadHandler> randar::CefHandler::GetDownloadHandler()
{
    return this;
}

::CefRefPtr<::CefDragHandler> randar::CefHandler::GetDragHandler()
{
    return this;
}

::CefRefPtr<::CefGeolocationHandler> randar::CefHandler::GetGeolocationHandler()
{
    return this;
}

::CefRefPtr<::CefKeyboardHandler> randar::CefHandler::GetKeyboardHandler()
{
    return this;
}

::CefRefPtr<::CefLifeSpanHandler> randar::CefHandler::GetLifeSpanHandler()
{
    return this;
}

::CefRefPtr<::CefLoadHandler> randar::CefHandler::GetLoadHandler()
{
    return this;
}

::CefRefPtr<::CefRequestHandler> randar::CefHandler::GetRequestHandler()
{
    return this;
}

// CefDownload implementations.
void randar::CefHandler::OnBeforeDownload(
    ::CefRefPtr<::CefBrowser> browser,
    ::CefRefPtr<::CefDownloadItem> item,
    const ::CefString& name,
    ::CefRefPtr<::CefBeforeDownloadCallback> callback
) {
    callback->Continue(name, true);
}

// CefLifeSpan implementations.
void randar::CefHandler::OnAfterCreated(::CefRefPtr<::CefBrowser> browser)
{
    CEF_REQUIRE_UI_THREAD();
    AutoLock lock_scope(this);

    this->browser = browser;

    CefLifeSpanHandler::OnAfterCreated(browser);
}

void randar::CefHandler::OnBeforeClose(::CefRefPtr<::CefBrowser> browser)
{
    CEF_REQUIRE_UI_THREAD();
    AutoLock lock_scope(this);

    browser = nullptr;
    //randar::StopBrowser();

    CefLifeSpanHandler::OnBeforeClose(browser);
}
