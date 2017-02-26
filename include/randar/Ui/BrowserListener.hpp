#ifndef RANDAR_UI_BROWSER_LISTENER_HPP
#define RANDAR_UI_BROWSER_LISTENER_HPP

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
