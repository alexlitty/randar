#ifndef RANDAR_UI_UI_HPP
#define RANDAR_UI_UI_HPP

#include <Awesomium/WebCore.h>
#include <Awesomium/BitmapSurface.h>
#include <randar/Engine/ResourceConsumer.hpp>

namespace randar
{
    class Ui : virtual public ResourceConsumer
    {
        Awesomium::WebCore* webCore;
        Awesomium::WebView* webView;

        Awesomium::BitmapSurface* surface;

    public:
        Ui();
        ~Ui();

        void update(randar::Gpu& gpu);
    };
}

#endif
