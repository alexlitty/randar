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
#include <randar/Ui/NativeCodeHandler.hpp>

namespace randar
{
    /**
     * @todo - Handle resizing
     * @todo - Handle engine-monitor painting over browser
     */
    class Browser
    : public ::CefApp,
      public ::CefClient,
      public ::CefContextMenuHandler,
      public ::CefDisplayHandler,
      public ::CefDownloadHandler,
      public ::CefDragHandler,
      public ::CefGeolocationHandler,
      public ::CefKeyboardHandler,
      public ::CefLifeSpanHandler,
      public ::CefLoadHandler,
      public ::CefRequestHandler,
      public ::CefRenderProcessHandler,
      public ::CefV8Handler
    {
        ::CefRefPtr<::CefBrowser> browser;
        ::CefRefPtr<::CefFrame> frame;
        randar::NativeCodeHandler* nativeCodeHandler;

    public:
        /**
         * Constructor.
         */
        Browser();

        /**
         * Destructor.
         */
        virtual ~Browser();

        /**
         * Tries to execute a CEF sub-process.
         *
         * Returns -1 if no sub-process was required by this instance.
         */

        int executeProcess(const ::CefMainArgs& mainArgs);

        /**
         * Checks whether the current page is loaded.
         */
        bool isLoading();

        /**
         * Performs browser work and processes message queues.
         */
        void update();

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
        virtual ::CefRefPtr<::CefRenderProcessHandler> GetRenderProcessHandler() override;

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
         * CefRenderProcessHandler implementations.
         */
        virtual void OnContextCreated(
            ::CefRefPtr<::CefBrowser> browser,
            ::CefRefPtr<::CefFrame> frame,
            ::CefRefPtr<::CefV8Context> context) override;

        /**
         * CefV8Handler implementations.
         */
        virtual bool Execute(
            const ::CefString& name,
            ::CefRefPtr<::CefV8Value> object,
            const ::CefV8ValueList& arguments,
            ::CefRefPtr<::CefV8Value>& returnValue,
            ::CefString& exception) override;

        /**
         * Sets the handler for native code requests.
         */
        void setNativeCodeHandler(randar::NativeCodeHandler* handler);

        /**
         * Handles messages between our main program and the CEF render process.
         *
         * @todo - Not used now. Remove if we continue not using it.
         */
        virtual bool OnProcessMessageReceived(
            ::CefRefPtr<::CefBrowser> browser,
            ::CefProcessId source,
            ::CefRefPtr<::CefProcessMessage> message) override;

        /**
         * Executes some JavaScript.
         */
        void executeJs(const std::string& code);

        IMPLEMENT_REFCOUNTING(Browser);
        IMPLEMENT_LOCKING(Browser);
    };
}

#endif
