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
         * Assignment.
         */
        Camcorder(const Camcorder& other);
        Camcorder& operator =(const Camcorder& other);
        Camcorder(Camcorder&& other);

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
         * Counts the images in the sequence.
         */
        uint32_t count() const;

        /**
         * Saves the image sequence to a video.
         */
        void save(const randar::Path& filepath);

        /**
         * Listens for new frames to capture.
         */
        virtual void onCanvasPresent() override;
    };

    /**
     * Node.js helper for intuitive camcorder creation.
     */
    Camcorder camcorder();
}

#endif
