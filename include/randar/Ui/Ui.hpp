#ifndef RANDAR_UI_UI_HPP
#define RANDAR_UI_UI_HPP

#include <randar/Engine/EngineMonitor.hpp>
#include <randar/Log/LogListener.hpp>
#include <randar/Project/Project.hpp>
#include <randar/Thread/ScopeLock.hpp>
#include <randar/Thread/TryLock.hpp>
#include <randar/Ui/Browser.hpp>
#include <randar/Ui/WindowListener.hpp>
#include <randar/Utility/tinyfiledialogs.h>

namespace randar
{
    /**
     * A bridge between an embedded browser, the Randar engine, and a Randar
     * project.
     */
    class Ui
    : virtual public LogListener,
      virtual public NativeCodeHandler,
      virtual public WindowListener
    {
        bool synced = false;

        /**
         * Files to be imported.
         *
         * Collected in a CEF thread, used in the main thread.
         */
        std::vector<File> importQueue;

        /**
         * New resources to be created.
         *
         * Collected in a CEF thread, used in the main thread.
         */
        std::vector<std::string> createResourceQueue;

        /**
         * Whether to save the project.
         */
        bool save = false;

    public:
        /**
         * GPU to use.
         */
        Gpu& gpu;

    protected:
        /**
         * Embedded browser that generates an HTML interface.
         */
        Browser& browser;

        /**
         * A monitor to draw resources, powered by Randar.
         */
        EngineMonitor monitor;

        /**
         * The active project loaded into Randar.
         */
        Project project;

    public:
        /**
         * Constructor.
         */
        Ui(Browser& initBrowser);

        /**
         * Handles program log messages.
         */
        virtual void onLog(const LogMessage& message) override;

        /**
         * Handles mouse events.
         */
        virtual void onMouseMove(
            const MousePosition& oldPosition,
            const MousePosition& position) override;

        virtual void onMouseButton(
            MouseButton button,
            const MouseModifiers& modifiers,
            const MousePosition& position,
            bool release) override;

        virtual void onScroll(const Vector& scroll) override;

        /**
         * Handles window events.
         */
        virtual void onResize(uint32_t width, uint32_t height) override;

        /**
         * Sends JSON data to the interface.
         */
        void sendAllData();
        void sendData(const Json& json);

        /**
         * Syncs data between the engine and interface, if necessary.
         */
        void sync();

        /**
         * Indicate a need to sync the engine and interface data.
         */
        void unsync();

        /**
         * Handles interface function calls for engine interaction.
         */
        virtual void execute(
            const std::string& name,
            const ::CefV8ValueList& arguments,
            ::CefRefPtr<::CefV8Value>& returnValue) override;

        /**
         * Runs Randar as an editor with a user-interface.
         *
         * When this method returns, the program should end.
         */
        void run();

    protected:
        /**
         * Runs through the browser and GLFW message loops.
         */
        void runMessageLoops();
    };
}

#endif
