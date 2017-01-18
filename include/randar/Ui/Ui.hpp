#ifndef RANDAR_UI_UI_HPP
#define RANDAR_UI_UI_HPP

#include <randar/Engine/Native.hpp>
#include <randar/Engine/Project.hpp>
#include <randar/Engine/Window.hpp>
#include <randar/Render/Framebuffer.hpp>
#include <randar/Render/Model.hpp>
#include <randar/Ui/Browser.hpp>
#include <randar/Utility/File.hpp>

namespace randar
{
    class Ui : virtual public Resource
    {
        Browser browser;
        Project project;

    public:
        Framebuffer defaultFramebuffer;
        ShaderProgram program;

        Framebuffer monitorFramebuffer;
        Model monitor;

        Ui();
        ~Ui();

        /**
         * Runs Randar as a GUI program.
         */
        void run();

    public:
        /**
         * Resizes the UI to fit the default window.
         */
        void resize();
        
        /**
         * Retrieves a list of film objects.
         */
        void getObjects(std::string type);

        /**
         * Synchronizes the engine with the interface.
         */
        void sync();

        /**
         * Draws the currently selected item onto a region of the interface.
         */
        void drawMonitor();

        /**
         * Resource initialization and destruction.
         */
        virtual void initialize() override;
        virtual void destroy() override;
    };

    /**
     * Retrieves the primary UI instance.
     */
    Ui& getUi();
}

#endif
