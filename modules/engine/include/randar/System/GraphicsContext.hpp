#ifndef RANDAR_SYSTEM_GRAPHICS_CONTEXT_HPP
#define RANDAR_SYSTEM_GRAPHICS_CONTEXT_HPP

#include <stdexcept>
#include <vector>
#include <GL/glew.h>
#include <GL/glx.h>
#include <randar/Utility/Unassignable.hpp>

namespace randar
{
    class Window;

    /**
     * A wrapper for OpenGL contexts.
     *
     * We use glew to map the correct gl calls to the desired OpenGL functions
     * and GPU behavior. On environments leveraging X11 and GLX, glew handles
     * multiple contexts seamlessly, as long as the contexts target the same
     * OpenGL version. The gl functions in this case are not binded to a
     * particular context, and will perform actions on the current context
     * automatically.
     *
     * On Windows in particular, glew must be re-initialized every time the
     * current context is switched. Windows binds the gl functions to a specific
     * context; A gl function created for one context only affects that context.
     * Re-initializing glew binds the global gl functions to the desired
     * context.
     *
     * As a result, this wraper is not compatible with Windows, and all contexts
     * created within a program must target the same OpenGL version. For now.
     *
     * A simple solution is to call glewInit every time the current context
     * changes. A performance-friendly solution is to save the gl functions
     * associated with this context, and only call gl functions saved within
     * this wrapper.
     *
     * This context, itself, does not expose a usable default framebuffer. To
     * perform off-screen rendering, render to a new framebuffer that is
     * associated with this context. To perform rendering in a window, use the
     * default framebuffers exposed by randar Windows.
     */
    class GraphicsContext : public Unassignable
    {
        /**
         * Display that was used to construct this context.
         */
        ::Display *display;

        /**
         * Information about the visual used by this context.
         */
        ::XVisualInfo *visual;

        /**
         * Available framebuffer configurations.
         */
        ::GLXFBConfig *fbConfigs;

        /**
         * Raw context this object wraps around.
         */
        ::GLXContext ctx;

        /**
         * GLX pixel buffer associated with this context.
         *
         * Not to be confused with OpenGL's pixel buffer objects.
         *
         * This is created to initialize our OpenGL context in a way that
         * enables windowless rendering. It is not used otherwise.
         */
        ::GLXPbuffer glxPixelBuffer;

        /**
         * Windows associated with this context, if any.
         *
         * We track these in case this context is destroyed before the windows
         * are, in which case we also uninitialize the windows.
         */
        std::vector<randar::Window*> windows;

    public:
        /**
         * Constructor.
         */
        GraphicsContext();

        /**
         * Destructor.
         */
        ~GraphicsContext();

        /**
         * Makes this context current without considering a window.
         *
         * This simply enables off-screen rendering via framebuffers. To enable
         * rendering to a window, make this context and the desired window
         * current.
         */
        void use();

        /**
         * Makes this context and a window current.
         *
         * This enables rendering to the given window in addition to off-screen
         * rendering.
         *
         * Essentially, this just allows you to render to the window's default
         * framebuffer.
         */
        void use(randar::Window& window);

        /**
         * Allow Randar windows to manipulate the ongoing list of associated
         * windows.
         */
        friend Window;
    };
}

#endif