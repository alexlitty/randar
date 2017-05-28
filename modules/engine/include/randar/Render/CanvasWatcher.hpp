#ifndef RANDAR_RENDER_CANVAS_WATCHER_HPP
#define RANDAR_RENDER_CANVAS_WATCHER_HPP

namespace randar
{
    class Canvas;

    class CanvasWatcher
    {
    protected:
        Canvas* _canvas;

    public:
        /**
         * Constructor.
         */
        CanvasWatcher();

        /**
         * Destructor.
         */
        virtual ~CanvasWatcher();

        /**
         * Start watching a canvas.
         */
        void watch(Canvas& newCanvas);

        /**
         * Stops watching a canvas.
         */
        void unwatch();

        /**
         * Whether this object is watching a canvas.
         */
        bool isWatching() const;

        /**
         * Retrieves the canvas being watched.
         */
        Canvas& canvas() const;

        /**
         * Invoked when the canvas presents a frame.
         */
        virtual void onCanvasPresent() = 0;

    };
}

#endif
