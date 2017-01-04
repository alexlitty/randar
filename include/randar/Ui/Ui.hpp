#ifndef RANDAR_UI_UI_HPP
#define RANDAR_UI_UI_HPP

#include <Awesomium/WebCore.h>
#include <Awesomium/BitmapSurface.h>
#include <randar/Render/Texture.hpp>

namespace randar
{
    class Ui : virtual public Resource
    {
        Awesomium::WebCore* webCore;
        Awesomium::WebView* webView;

        Awesomium::BitmapSurface* surface;

    public:
        Texture texture;

        Ui();
        ~Ui();

        void update(randar::Gpu& gpu);

        /**
         * Resource initialization and destruction.
         */
        virtual void initialize(randar::Gpu& gpu) override;
        virtual void destroy(randar::Gpu& gpu) override;
    };
}

#endif
