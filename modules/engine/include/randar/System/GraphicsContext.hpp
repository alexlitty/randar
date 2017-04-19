#ifndef RANDAR_SYSTEM_GRAPHICS_CONTEXT_HPP
#define RANDAR_SYSTEM_GRAPHICS_CONTEXT_HPP

#include <randar/Utility/Unassignable.hpp>

namespace randar
{
    /**
     * A simple wrapper for OpenGL contexts.
     *
     * Randar demands only one context may exist at any time for a single
     * process. Any work that requires multiple contexts must be performed in
     * separate processes.
     *
     * If we allowed multiple contexts within a process, Randar would have to
     * perform checks and context switches that hinder performance.
     *
     * Any number of threads may share the process-wide context.
     */
    class GraphicsContext : public Unassignable
    {
        /**
         * Constructor.
         *
         * Don't let this be called multiple times in a single process. Just
         * call the static require method and everyone will be happy.
         */
        GraphicsContext();

        /**
         * Destructor.
         */
        ~GraphicsContext();

    public:
        /**
         * Signals the requirement for a process-wide graphics context.
         *
         * If the context is not yet initialized, it is initialized immediately.
         * Nothing happens if the context is already initialized; It is safe to
         * call this repeatedly.
         *
         * The context is assigned to randar::ctx.
         */
        static void require();

        /**
         * Destroys the process-wide graphics context.
         *
         * After destruction, randar::ctx is set to a nullptr.
         *
         * You probably won't ever need to call this, but it's here for whatever
         * evil plan you have.
         */
        static void destroy();
    };

    /**
     * Process-wide graphics context.
     *
     * When a context is needed, call GraphicsContext::require. Until that is
     * called, ctx is a nullptr. If you ever need to destroy this, call
     * GraphicsContext::destroy.
     */
    extern GraphicsContext* ctx;
}

#endif
