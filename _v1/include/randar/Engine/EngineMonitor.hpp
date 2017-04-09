#ifndef RANDAR_UI_ENGINE_MONITOR_HPP
#define RANDAR_UI_ENGINE_MONITOR_HPP

#include <randar/Engine/Window.hpp>
#include <randar/Render/Framebuffer.hpp>
#include <randar/Render/Model.hpp>
#include <randar/Render/ShaderProgram.hpp>
#include <randar/Thread/Lockable.hpp>
#include <randar/Utility/File.hpp>

namespace randar
{
    class EngineMonitor
    : virtual public Resource,
              public Lockable
    {
    public:
        ShaderProgram screenProgram;
        ShaderProgram modelProgram;
        ShaderProgram modelWireframeProgram;
        ShaderProgram textureProgram;
        Model screen;

        bool newTarget;

        Framebuffer defaultFramebuffer;

        Framebuffer monitorFramebuffer;
        Camera& camera;

        /**
         * Model to monitor.
         */
        Model *targetModel;

        /**
         * Texture to monitor, and a model to help show the texture.
         */
        Texture *targetTexture;
        Model targetTextureModel;

        EngineMonitor();
        ~EngineMonitor();

        /**
         * Resizes the monitor to fit a window.
         */
        void resize(::GLFWwindow& window = randar::getDefaultWindow());

        /**
         * Resizes the monitor.
         */
        void resize(uint32_t width, uint32_t height);

        /**
         * Clears the monitoring target.
         */
        void clearTarget();

        /**
         * Sets the monitoring target.
         *
         * The target must be initialized onto the monitor later.
         */
        void setTarget(Model &model);
        void setTarget(Texture &texture);

        /**
         * Whether the monitoring target has been changed.
         *
         * If this returns true, the new target should be initialized onto the
         * monitor.
         */
        bool hasNewTarget() const;

        /**
         * Initializes the current target onto the monitor.
         */
        void initializeTarget();
        
        /**
         * Draws the monitor target.
         *
         * If no target is set, nothing is drawn.
         */
        void draw();
    };
}

#endif