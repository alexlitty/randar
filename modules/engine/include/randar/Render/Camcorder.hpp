#ifndef RANDAR_RENDER_CAMCORDER_HPP
#define RANDAR_RENDER_CAMCORDER_HPP

#include <randar/Render/CanvasWatcher.hpp>
#include <randar/Render/Image.hpp>
#include <randar/System/Path.hpp>

namespace randar
{
    class Camcorder : virtual public CanvasWatcher
    {
        /**
         * Help swig identify inherited methods.
         */
        using CanvasWatcher::watch;
        using CanvasWatcher::unwatch;
        using CanvasWatcher::isWatching;
        using CanvasWatcher::canvas;

    protected:
        randar::Path _imagesDirectory;
        std::vector<randar::Path> imagePaths;

    public:
        /**
         * Constructors.
         */
        Camcorder();
        Camcorder(Canvas& canvas);

        /**
         * Destructor.
         */
        virtual ~Camcorder();
        
        /**
         * Directory to save the image sequence in.
         */
        void imagesDirectory(const std::string& newDir);
        std::string imagesDirectory() const;

        /**
         * Adds an image to the sequence.
         */
        void push(Image& image);

        /**
         * Saves the image sequence to a video.
         */
        void toVideo(const std::string& filename);

        /**
         * Listens for new frames to capture.
         */
        void onCanvasPresent();
    };

    /**
     * Node.js helper for intuitive camcorder creation.
     */
    Camcorder camcorder();
}

#endif
