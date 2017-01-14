#ifndef RANDAR_UI_CEF_HPP
#define RANDAR_UI_CEF_HPP

#include <cef/include/cef_app.h>

namespace randar
{
    class Cef : public ::CefApp
    {
        IMPLEMENT_REFCOUNTING(Cef);

    public:
        Cef();
        virtual ~Cef();
    };
}

#endif
