#ifndef RANDAR_UI_UI_HPP
#define RANDAR_UI_UI_HPP

#include <Awesomium/WebCore.h>
#include <Awesomium/BitmapSurface.h>
#include <Awesomium/STLHelpers.h>
#include <randar/Render/Framebuffer.hpp>
#include <randar/Render/Model.hpp>
#include <randar/Ui/Mouse.hpp>
#include <randar/Utility/File.hpp>

namespace randar
{
    class Ui : virtual public Resource
    {
        Framebuffer defaultFramebuffer;
        Awesomium::WebCore* webCore;
        Awesomium::WebView* webView;

        Awesomium::BitmapSurface* surface;
        bool isReady;

    public:
        ShaderProgram program;
        Model interface;
        Texture interfaceTexture;

        Framebuffer monitorFramebuffer;
        Model monitor;

        Ui();
        ~Ui();

    protected:
        /**
         * Performs a sanity check on Awesomium's web view.
         *
         * A runtime error is thrown if the check fails.
         */
        void check();

        /**
         * Executes a Javascript method on the top-level "randar" object.
         */
        Awesomium::JSValue jsExecute(const std::string& methodName, bool ignoreResult = false);

    public:
        /**
         * Resizes the UI to fit the default window.
         */
        void resize();
        
        /**
         * Handles mouse events.
         */
        void setMousePosition(int x, int y);
        void pressMouse(MouseButton button);
        void releaseMouse(MouseButton button);

        /**
         * Retrieves a list of film objects.
         */
        void getObjects(std::string type);

        /**
         * Draws the UI.
         */
        void draw();

        /**
         * Resource initialization and destruction.
         */
        virtual void initialize() override;
        virtual void destroy() override;
    };

    /**
     * Retrieves the primary UI instance.
     */
    Ui& getUi();
}

#endif
