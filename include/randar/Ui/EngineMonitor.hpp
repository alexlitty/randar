#ifndef RANDAR_UI_UI_HPP
#define RANDAR_UI_UI_HPP

#include <randar/Render/Framebuffer.hpp>
#include <randar/Render/Model.hpp>
#include <randar/Utility/File.hpp>

namespace randar
{
    class EngineMonitor : virtual public Resource
    {
    public:
        Framebuffer defaultFramebuffer;
        ShaderProgram program;

        Framebuffer monitorFramebuffer;
        Model monitor;

        EngineMonitor();
        ~EngineMonitor();

        /**
         * Resizes the monitor to fit the window.
         */
        void resize();
        
        /**
         * Draws the currently selected item onto a region of the interface.
         */
        void draw();

        /**
         * Resource initialization and destruction.
         */
        virtual void initialize() override;
        virtual void destroy() override;
    };
}

#endif
