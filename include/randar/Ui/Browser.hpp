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
#include <randar/Ui/EngineMonitor.hpp>

namespace randar
{
    class BrowserBridge;

    /**
     * @todo - Handle resizing
     * @todo - Handle engine-monitor painting over browser
     */
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
        EngineMonitor& monitor;

    public:
        /**
         * Constructor.
         */
        Browser(EngineMonitor& initMonitor, ::CefRefPtr<BrowserBridge> bridge);

        /**
         * Destructor.
         */
        ~Browser();

        /**
         * Performs browser work and draws the engine monitor.
         */
        void update();

        /**
         * Retrieves the browser associated with this handler.
         */
        virtual ::CefRefPtr<::CefBrowser> GetRawBrowser();

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

        /**
         * @@ CefClient
         */
        virtual bool OnProcessMessageReceived(
            ::CefRefPtr<::CefBrowser> browser,
            ::CefProcessId source,
            ::CefRefPtr<::CefProcessMessage> message) override;

        IMPLEMENT_REFCOUNTING(Browser);
        IMPLEMENT_LOCKING(Browser);
    };

    /**
     * 
     */
    struct BrowserBridge
    : public ::CefApp,
      public ::CefRenderProcessHandler
    {
        virtual ::CefRefPtr<::CefRenderProcessHandler> GetRenderProcessHandler() override;

        virtual bool OnProcessMessageReceived(
            ::CefRefPtr<::CefBrowser> browser,
            ::CefProcessId source,
            ::CefRefPtr<::CefProcessMessage> message) override;

        virtual void OnContextCreated(
            ::CefRefPtr<::CefBrowser> browser,
            ::CefRefPtr<::CefFrame> frame,
            ::CefRefPtr<::CefV8Context> context) override;

        IMPLEMENT_REFCOUNTING(BrowserBridge);
    };
}

#endif
