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

    public:
        ShaderProgram program;
        Model interface;
        Texture interfaceTexture;

        Framebuffer monitorFramebuffer;
        Model monitor;

        Ui();
        ~Ui();

        void resize();
        
        /**
         * Handles mouse events.
         */
        void setMousePosition(int x, int y);
        void pressMouse(MouseButton button);
        void releaseMouse(MouseButton button);

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
