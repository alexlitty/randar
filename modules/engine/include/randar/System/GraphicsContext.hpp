#ifndef RANDAR_SYSTEM_GRAPHICS_CONTEXT_HPP
#define RANDAR_SYSTEM_GRAPHICS_CONTEXT_HPP

#include <map>
#include <set>
#include <stdexcept>
#include <vector>
#include <randar/Render/ShaderType.hpp>
#include <randar/Utility/Gl.hpp>

namespace randar
{
    class GraphicsContextResource;

    template <GLenum T, typename U> class GlBuffer;
    typedef GlBuffer<GL_ARRAY_BUFFER, float> FloatArrayBuffer;
    typedef GlBuffer<GL_ELEMENT_ARRAY_BUFFER, unsigned int> IndexBuffer;

    class VertexBuffer;
    class Geometry;

    class Shader;
    class ShaderProgram;

    class Renderbuffer;
    class Framebuffer;
    class Texture;
    class Window;

    class Monitor;

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
    class GraphicsContext
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
         * Default shaders and shader program for this context.
         *
         * Created automatically as necessary.
         */
        std::map<ShaderType, Shader*> dShaders;
        ShaderProgram* dShaderProgram = nullptr;

    public:
        /**
         * Resources which are associated with this context.
         *
         * These resources may exist after the lifetime of the context, to be
         * used on other contexts or for other non-rendering purposes.
         */
        std::set<GraphicsContextResource*> resources;

        /**
         * Resources which are owned by this context.
         *
         * Owned resources are always associated with this context.
         */
        std::set<GraphicsContextResource*> ownedResources;

        /**
         * Disable assignment.
         */
        GraphicsContext(const GraphicsContext& other) = delete;
        GraphicsContext& operator =(const GraphicsContext& other) = delete;

        /**
         * Constructor.
         */
        GraphicsContext();

        /**
         * Destructor.
         */
        ~GraphicsContext();

        /**
         * Queries the version of OpenGL being used.
         */
        std::string version();

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
         * Waits for any queued OpenGL commands to be completed.
         */
        void sync();

    protected:
        /**
         * Current GL status.
         *
         * Used in the check method. Allocated here for performance.
         */
        GLenum status;

    public:
        /**
         * Checks for any errors reported by OpenGL.
         *
         * If an error has occurred, an exception is thrown with the given
         * message, which should indicate the action previously performed.
         *
         * Ensure this context is current before invoking. To prevent an
         * infinite loop, this does not make the context current.
         */
        void check(const std::string& message);

        /**
         * Associates and unassociates a resource with this context.
         */
        void associate(GraphicsContextResource& resource);
        void unassociate(GraphicsContextResource& resource);

        /**
         * Checks if a resource is associated with the context.
         */
        bool isAssociated(GraphicsContextResource& resource);

        /**
         * Counts the resources associated with the context.
         */
        unsigned int resourceCount() const;

        /**
         * Resource creators.
         *
         * These must be used in the Node.js adapter so we can destruct
         * resources in a predictable manner.
         */
        FloatArrayBuffer& floatArrayBuffer();
        IndexBuffer& indexBuffer();

        VertexBuffer& vertexBuffer();
        Geometry& geometry();

        Renderbuffer& renderbuffer(
            uint32_t width,
            uint32_t height,
            const std::string& type);

        Framebuffer& framebuffer();

        randar::Texture& texture(
            uint32_t width,
            uint32_t height,
            const std::string& type = "rgba");

        randar::Window& window(uint32_t width, uint32_t height);

        randar::Monitor& monitor(randar::Geometry& geometry);

        /**
         * Default resources.
         */
        Shader& defaultShader(ShaderType type);
        ShaderProgram& defaultShaderProgram();

        /**
         * Allow Randar windows to manipulate the ongoing list of associated
         * windows.
         */
        friend Window;
    };
}

#endif
