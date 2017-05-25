#ifndef RANDAR_SYSTEM_FB_CONFIG_HPP
#define RANDAR_SYSTEM_FB_CONFIG_HPP

#include <vector>
#include <randar/Utility/Gl.hpp>

namespace randar
{
    /**
     * GLX framebuffer configuration attributes.
     *
     * No relationship with OpenGL framebuffers.
     *
     * This is a structure of potential attributes. It can be used to query the
     * configurations available, or describe an existing configuration.
     */
    class FbAttributes
    {
    protected:
        std::vector<int> raw;

    public:
        bool renderable = true;

        int visualType   = GLX_TRUE_COLOR;
        int drawableType = GLX_WINDOW_BIT;

        bool doublebuffer = true;

        int redSize   = 8;
        int greenSize = 8;
        int blueSize  = 8;
        int alphaSize = 8;

        int depthSize   = 24;
        int stencilSize = 8;

        /**
         * Constructor.
         */
        FbAttributes();

        /**
         * Destructor.
         */
        ~FbAttributes();

        /**
         * Generates an array of the attributes for GLX operations.
         *
         * Allocation and freeing is handled within the class.
         */
        int* data();
    };

    /**
     * An existing GLX framebuffer configuration.
     *
     * No relationship with OpenGL framebuffers.
     */
    class FbConfig : public FbAttributes
    {
    public:
        Display* display;
        ::GLXFBConfig& glx;

        /**
         * Constructor.
         *
         * Queries GLX and fills the attributes structure.
         */
        FbConfig(Display* initDisplay, ::GLXFBConfig& initGlx);

    protected:
        /**
         * Queries GLX for an attribute.
         */
        void query(int attribute, bool& value);
        void query(int attribute, int& value);
    };
}

#endif
