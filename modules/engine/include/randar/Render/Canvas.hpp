#ifndef RANDAR_RENDER_CANVAS_HPP
#define RANDAR_RENDER_CANVAS_HPP

#include <set>
#include <randar/Render/Camera.hpp>
#include <randar/Render/CanvasWatcher.hpp>
#include <randar/Render/Model.hpp>
#include <randar/Render/TextureCollection.hpp>
#include <randar/Utility/Timer.hpp>

namespace randar
{
    class Camcorder;
    class Framebuffer;
    class World;

    class BaseLight;
    typedef std::vector<BaseLight*> LightCollection;

    /**
     * An object which can be drawn upon.
     */
    class Canvas
    {
        /**
         * Objects watching this canvas for presentations.
         */
        std::set<CanvasWatcher*> watchers;

        /**
         * Timer used for fps throttling.
         */
        Timer throttleTimer;

        /**
         * Desired frames per second to throttle at.
         *
         * Zero indicates no throttling desired.
         */
        uint16_t canvasFps;

        /**
         * Camera used while drawing to the canvas.
         */
        Camera canvasCamera;

    public:
        /**
         * Constructor.
         */
        Canvas(uint16_t initFps = 0);

        /**
         * Destructor.
         */
        virtual ~Canvas();

        /**
         * Sets and retrieves the desired fps.
         */
        void fps(uint16_t newFps);
        uint16_t fps() const;

        /**
         * Retrieves a reference to the canvas camera.
         */
        Camera& camera();

        /**
         * Retrieves the underlying framebuffer used for drawing.
         */
        virtual Framebuffer& framebuffer() = 0;

        /**
         * Clears the canvas with a color.
         *
         * Default color is an opaque dark purple. The default is purposely not
         * black; Buggy rendering behavior usually shows up as black, making
         * it less likely the behavior is seen.
         */
        void clear(const Color& color = Color(0.29, 0.00, 0.29));

        /**
         * Draws geometry to the canvas.
         *
         * Defaults are provided for the shader program, transform, and textures
         * if omitted.
         */
        void draw(Geometry& geometry);

        void draw(Geometry& geometry, TextureCollection& textures);
        void draw(Geometry& geometry, ShaderProgram& program);
        void draw(Geometry& geometry, Transform& transform);

        void draw(
            Geometry& geometry,
            Transform& transform,
            ShaderProgram& program);

        void draw(
            Geometry& geometry,
            TextureCollection& textures,
            Transform& transform,
            ShaderProgram& program);

        /**
         * Draws a model to the canvas.
         *
         * Nothing happens if the model has no geometry.
         */
        void draw(Model& model);

    protected:
        /**
         * Draws a model to the canvas with light hints.
         *
         * Do not call this directly. It is called when lightmaps have already
         * been generated.
         */
        void draw(Model& model, LightCollection& lights);

    public:
        /**
         * Draws a world to the canvas.
         */
        void draw(World& world, bool withLights = true);

        /**
         * Retrieves the contents of this canvas as an image.
         *
         * In doublebuffering scenarios the back buffer is read. It is thus
         * important to call this before presenting the canvas, since
         * presentation may fill the back buffer with undefined contents.
         */
        Image image();

        /**
         * Presents the canvas rendering.
         *
         * This call throttles execution to meet the desired fps unless it is
         * set to zero. If recording is enabled, the current frame is captured.
         *
         * Children may extend this depending on their needs. For example, if
         * a child leverages doublebuffering, the back and front framebuffers
         * should be swapped in this call. If extended, children should call the
         * base.
         *
         * The nature of some children may not require this call to perform
         * basic rendering. It is still recommended to call it; The user will benefit from
         * seamless throttling and recording.
         */
        virtual void present();

        /**
         * Gets a new camcorder for this canvas.
         */
        Camcorder camcorder();

        /**
         * Let CanvasWatcher objects modify the internal watchers list.
         */
        friend CanvasWatcher;
    };
}

#endif
