#ifndef RANDAR_SYSTEM_MONITOR_HPP
#define RANDAR_SYSTEM_MONITOR_HPP

#include <randar/Render/Geometry.hpp>
#include <randar/System/Window.hpp>

namespace randar
{
    /**
     * A general-purpose resource monitor.
     */
    class Monitor : virtual public GraphicsContextResource
    {
        /**
         * Window used by the monitor.
         */
        randar::Window* win = nullptr;

        /**
         * Resource being monitored.
         *
         * Only one of these may be non-null at any time.
         */
        Geometry* geo = nullptr;

    public:
        /**
         * Constructor.
         */
        Monitor(GraphicsContext& context, Geometry& geometry);

        /**
         * Assignment.
         */
        Monitor(const Monitor& other) = delete;
        Monitor& operator =(const Monitor& other) = delete;
        Monitor(Monitor&& other);

        /**
         * Destructor.
         */
        ~Monitor();

        /**
         * Presents the monitor to the screen.
         */
        void present();
    };
}

#endif
