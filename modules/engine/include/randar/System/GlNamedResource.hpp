#ifndef RANDAR_SYSTEM_GL_NAMED_RESOURCE_HPP
#define RANDAR_SYSTEM_GL_NAMED_RESOURCE_HPP

#include <randar/System/GraphicsContext.hpp>

namespace randar
{
    /**
     * A helper for single, named OpenGL resources.
     *
     * Use with GraphicsContextResource for seamless Context integration. This
     * is simply provides a glName member and its getter.
     */
    class GlNamedResource
    {
    protected:
        GLuint glName;

    public:
        /**
         * Default constructor.
         */
        GlNamedResource();

        /**
         * Destructor.
         */
        virtual ~GlNamedResource();

        /**
         * Gets the GL name for this resource.
         */
        GLuint getGlName() const;
    };
}

#endif
