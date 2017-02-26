#ifndef RANDAR_UI_CEF_HANDLER_HPP
#define RANDAR_UI_CEF_HANDLER_HPP

// Required by CEF.
#define NDEBUG

#include <cef/include/base/cef_lock.h>
#include <cef/include/cef_app.h>
#include <cef/include/cef_client.h>
#include <cef/include/wrapper/cef_helpers.h>
#include <cef/include/capi/cef_base_capi.h>
#include <randar/Render/Framebuffer.hpp>
#include <randar/Render/Model.hpp>
#include <randar/Render/ShaderProgram.hpp>
#include <randar/Engine/Native.hpp>
#include <randar/Engine/Window.hpp>
#include <randar/Ui/NativeCodeHandler.hpp>
#include <randar/Ui/BrowserListener.hpp>

namespace randar
{
    /**
     * @todo - Handle resizing
     * @todo - Handle engine-monitor painting over browser
     */
    class Browser
    : public ::CefApp,
      public ::CefClient,
      public ::CefDownloadHandler,
      public ::CefLifeSpanHandler,
      public ::CefLoadHandler,
      public ::CefRenderHandler,
      public ::CefRenderProcessHandler,
      public ::CefV8Handler
    {
        ::CefRefPtr<::CefBrowser> browser;
        ::CefRefPtr<::CefFrame> frame;
        randar::NativeCodeHandler* nativeCodeHandler;

        std::vector<randar::BrowserListener*> listeners;

    public:
        Model* screen;
        Texture* texture;

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
         * Registers a new browser listener.
         *
         * These listeners are notified of specific browser events.
         */
        void registerListener(randar::BrowserListener* listener);

        /**
         * Gets the browser host object.
         */
        ::CefRefPtr<::CefBrowserHost> getHost();

        /**
         * Checks whether the current page is loaded.
         */
        bool isLoading();

        /**
         * Performs browser work and processes message queues.
         */
        void update();

        /**
         * Resizes the browser to fit a window.
         */
        void resize(::GLFWwindow& window = randar::getDefaultWindow());

        /**
         * Resizes the browser to specific dimensions.
         */
        void resize(uint32_t width, uint32_t height);

        /**
         * CefClient implementations.
         */
        virtual ::CefRefPtr<::CefDownloadHandler> GetDownloadHandler() override;
        virtual ::CefRefPtr<::CefLifeSpanHandler> GetLifeSpanHandler() override;
        virtual ::CefRefPtr<::CefLoadHandler> GetLoadHandler() override;
        virtual ::CefRefPtr<::CefRenderHandler> GetRenderHandler() override;
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
         * CefRenderHandler implementations.
         */
        virtual bool GetViewRect(
            ::CefRefPtr<::CefBrowser> browser,
            ::CefRect& rect) override;

        virtual void OnCursorChange(
            ::CefRefPtr<::CefBrowser> browser,
            unsigned long cursor,
            ::CefRenderHandler::CursorType type,
            const ::CefCursorInfo& custom_cursor_info) override;

        virtual void OnPaint(
            ::CefRefPtr<::CefBrowser> browser,
            ::CefRenderHandler::PaintElementType type,
            const ::CefRenderHandler::RectList& dirtyRects,
            const void* rawBuffer,
            int width,
            int height) override;

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
