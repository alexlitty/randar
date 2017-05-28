#include <randar/Render/Canvas.hpp>
#include <randar/Render/CanvasWatcher.hpp>

// Constructor.
randar::CanvasWatcher::CanvasWatcher()
: _canvas(nullptr)
{

}

// Destructor.
randar::CanvasWatcher::~CanvasWatcher()
{
    this->unwatch();
}

// Start watching a canvas.
void randar::CanvasWatcher::watch(randar::Canvas& newCanvas)
{
    this->unwatch();

    this->_canvas = &newCanvas;
    newCanvas.watchers.insert(this);
}

// Stops watching a canvas.
void randar::CanvasWatcher::unwatch()
{
    if (this->isWatching()) {
        this->canvas().watchers.erase(this);
        this->_canvas = nullptr;
    }
}

// Whether this object is watching a canvas.
bool randar::CanvasWatcher::isWatching() const
{
    return this->_canvas != nullptr;
}

// Retrieves the canvas being watched.
randar::Canvas& randar::CanvasWatcher::canvas()
{
    if (!this->isWatching()) {
        throw std::runtime_error("No canvas is being watched");
    }

    return *this->_canvas;
}
