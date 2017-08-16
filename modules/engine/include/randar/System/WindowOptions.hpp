#ifndef RANDAR_SYSTEM_WINDOW_OPTIONS
#define RANDAR_SYSTEM_WINDOW_OPTIONS

namespace randar
{
    struct WindowOptions
    {
        /**
         * Whether the window should be displayed over all others.
         */
        bool top;

        /**
         * Constructor.
         */
        WindowOptions();
    };
}

#endif
