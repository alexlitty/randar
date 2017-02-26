#ifndef RANDAR_UI_BROWSER_LISTENER_HPP
#define RANDAR_UI_BROWSER_LISTENER_HPP

#include <randar/Ui/Cursor.hpp>

namespace randar
{
    /**
     * An object that receives browser events.
     */
    class BrowserListener
    {
    public:
        virtual void onCursorChange(randar::Cursor type) = 0;
    };
}

#endif
