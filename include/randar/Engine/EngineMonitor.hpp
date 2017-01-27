#ifndef RANDAR_UI_ENGINE_MONITOR_HPP
#define RANDAR_UI_ENGINE_MONITOR_HPP

#include <randar/Render/Framebuffer.hpp>
#include <randar/Render/Model.hpp>
#include <randar/Render/ShaderProgram.hpp>
#include <randar/Utility/File.hpp>

namespace randar
{
    class EngineMonitor : virtual public Resource
    {
        ShaderProgram screenProgram;
        ShaderProgram modelProgram;
        Model screen;

    public:
        Framebuffer defaultFramebuffer;

        Framebuffer monitorFramebuffer;
        Camera& camera;

        Model *targetModel;

        EngineMonitor();
        ~EngineMonitor();

        /**
         * Resizes the monitor to fit the window.
         */
        void resize();

        /**
         * Clears the monitoring target.
         */
        void clearTarget();

        /**
         * Sets the monitoring target.
         */
        void setTarget(Model &model);
        
        /**
         * Draws the monitor target.
         *
         * If no target is set, nothing is drawn.
         */
        void draw();
    };
}

#endif
