#ifndef RANDAR_UI_UI_HPP
#define RANDAR_UI_UI_HPP

#include <randar/Engine/EngineMonitor.hpp>
#include <randar/Engine/Project.hpp>
#include <randar/Ui/Browser.hpp>

namespace randar
{
    /**
     * A bridge between an embedded browser, the Randar engine, and a Randar
     * project.
     */
    class Ui
    {
        /**
         * GPU to use.
         */
        Gpu& gpu;

        /**
         * Window that contains the interface.
         */
        ::GLFWwindow* window;

        /**
         * Embedded browser that generates an HTML interface.
         */
        Browser& browser;

        /**
         * A monitor to draw resources, powered by Randar.
         */
        EngineMonitor monitor;

        /**
         * The active project shown in the interface.
         */
        Project project;

    public:

        /**
         * Constructor.
         */
        Ui(Browser& initBrowser);

        /**
         * Runs Randar as an editor with a user-interface.
         *
         * Updates the embedded browser and draws the engine monitor beside the
         * HTML interface. Also facilitates any communication needed between
         * the Randar and browser engines.
         *
         * The embedded browser automatically draws itself to the default
         * framebuffer. It's magical, you need not worry about it.
         *
         * When this method returns, the program should end.
         */
        void execute();
    };
}

#endif
