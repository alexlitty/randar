#ifndef RANDAR_UI_CEF_HANDLER_HPP
#define RANDAR_UI_CEF_HANDLER_HPP

// Required by CEF.
#define NDEBUG

#include <cef/include/base/cef_lock.h>
#include <cef/include/cef_app.h>
#include <cef/include/cef_client.h>
#include <cef/include/wrapper/cef_helpers.h>
#include <cef/include/capi/cef_base_capi.h>
#include <randar/Engine/Native.hpp>
#include <randar/Engine/Window.hpp>

namespace randar
{
    class Browser
    : public ::CefClient,
      public ::CefContextMenuHandler,
      public ::CefDisplayHandler,
      public ::CefDownloadHandler,
      public ::CefDragHandler,
      public ::CefGeolocationHandler,
      public ::CefKeyboardHandler,
      public ::CefLifeSpanHandler,
      public ::CefLoadHandler,
      public ::CefRequestHandler
    {
        ::CefRefPtr<::CefBrowser> browser;

    public:
        /**
         * Constructor.
         */
        Browser();

        /**
         * Destructor.
         */
        ~Browser();

        /**
         * Retrieves the browser associated with this handler.
         */
        virtual ::CefRefPtr<::CefBrowser> GetBrowser();

        /**
         * CefClient implementations.
         */
        virtual ::CefRefPtr<::CefContextMenuHandler> GetContextMenuHandler() override;
        virtual ::CefRefPtr<::CefDisplayHandler> GetDisplayHandler() override;
        virtual ::CefRefPtr<::CefDownloadHandler> GetDownloadHandler() override;
        virtual ::CefRefPtr<::CefDragHandler> GetDragHandler() override;
        virtual ::CefRefPtr<::CefGeolocationHandler> GetGeolocationHandler() override;
        virtual ::CefRefPtr<::CefKeyboardHandler> GetKeyboardHandler() override;
        virtual ::CefRefPtr<::CefLifeSpanHandler> GetLifeSpanHandler() override;
        virtual ::CefRefPtr<::CefLoadHandler> GetLoadHandler() override;
        virtual ::CefRefPtr<::CefRequestHandler> GetRequestHandler() override;

        /**
         * CefDownload implementations.
         */
        virtual void OnBeforeDownload(
            ::CefRefPtr<::CefBrowser> browser,
            ::CefRefPtr<::CefDownloadItem> item,
            const ::CefString& name,
            ::CefRefPtr<::CefBeforeDownloadCallback> callback) override;

        /**
         * CefLifeSpan implementations.
         */
        virtual void OnAfterCreated(::CefRefPtr<::CefBrowser> browser) override;
        virtual void OnBeforeClose(::CefRefPtr<::CefBrowser> browser) override;

        IMPLEMENT_REFCOUNTING(Browser);
        IMPLEMENT_LOCKING(Browser);
    };
}

#endif
