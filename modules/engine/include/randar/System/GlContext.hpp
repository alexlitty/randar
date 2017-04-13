#ifndef RANDAR_SYSTEM_GLCONTEXT_HPP
#define RANDAR_SYSTEM_GLCONTEXT_HPP

#include <GL/glew.h>
#include <GL/glx.h>
#include <randar/Utility/Version.hpp>

#define GLX_CONTEXT_MAJOR_VERSION_ARB 0x2091
#define GLX_CONTEXT_MINOR_VERSION_ARB 0x2092
typedef GLXContext (*glXCreateContextAttribsARBProc)(
    Display*,
    GLXFBConfig,
    GLXContext,
    Bool,
    const int*);

namespace randar
{
    struct GlContext
    {
        Version version;

        /**
         * Default constructor.
         */
        GlContext();

        /**
         * Dummy copy constructor.
         *
         * Unconditionally throws an exception.
         */
        GlContext(const GlContext& other);

        /**
         * Destructor.
         */
        ~GlContext();

        /**
         * Dummy assignment operator.
         *
         * Unconditionally throws an exception.
         */
        GlContext& operator =(const GlContext& other);
    };
}

#endif
