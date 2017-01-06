#ifndef RANDAR_UI_UI_HPP
#define RANDAR_UI_UI_HPP

#include <Awesomium/WebCore.h>
#include <Awesomium/BitmapSurface.h>
#include <Awesomium/STLHelpers.h>
#include <randar/Render/Model.hpp>
#include <randar/Render/Texture.hpp>
#include <randar/Utility/File.hpp>

namespace randar
{
    class Ui : virtual public Resource
    {
        Awesomium::WebCore* webCore;
        Awesomium::WebView* webView;

        Awesomium::BitmapSurface* surface;

    public:
        ShaderProgram program;
        Model model;
        Texture texture;

        Ui();
        ~Ui();

        void draw(randar::Gpu& gpu);

        /**
         * Resource initialization and destruction.
         */
        virtual void initialize(randar::Gpu& gpu) override;
        virtual void destroy(randar::Gpu& gpu) override;
    };
}

#endif
