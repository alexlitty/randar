#ifndef RANDAR_UI_UI_HPP
#define RANDAR_UI_UI_HPP

#include <randar/Engine/Project.hpp>
#include <randar/Render/Framebuffer.hpp>
#include <randar/Render/Model.hpp>
#include <randar/Ui/Cef.hpp>
#include <randar/Utility/File.hpp>

namespace randar
{
    class Ui : virtual public Resource
    {
        ::CefRefPtr<randar::Cef> cef;

        Framebuffer defaultFramebuffer;
        Project project;

    public:
        ShaderProgram program;
        Model interface;
        Texture interfaceTexture;

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
         * Handles mouse events.
         */
        //void setMousePosition(int x, int y);
        //void pressMouse(MouseButton button);
        //void releaseMouse(MouseButton button);

        /**
         * Handles keyboard input.
         */
        void sendKey(int key);

        /**
         * Retrieves a list of film objects.
         */
        void getObjects(std::string type);

        /**
         * Synchronizes the engine with the interface.
         */
        void sync();

        /**
         * Draws the UI.
         */
        void draw();

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
