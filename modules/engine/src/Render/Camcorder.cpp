#include <randar/Render/Canvas.hpp>
#include <randar/Render/Camcorder.hpp>
#include <randar/System/Execute.hpp>

// Constructors.
randar::Camcorder::Camcorder()
{

}

randar::Camcorder::Camcorder(randar::Canvas& canvas)
{
    this->watch(canvas);
}

// Destructor.
randar::Camcorder::~Camcorder()
{

}

// Directory to save the image sequence in.
void randar::Camcorder::imagesDirectory(const std::string& newDir)
{
    this->_imagesDirectory = newDir;
}

std::string randar::Camcorder::imagesDirectory() const
{
    return this->_imagesDirectory.toString();
}

// Adds an image to the sequence.
void randar::Camcorder::push(randar::Image& image)
{
    std::string basename = std::to_string(this->imagePaths.size()) + ".png";
    while (basename.length() < 12) {
        basename = "0" + basename;
    }

    randar::Path imagePath = this->_imagesDirectory.child(basename);
    image.save(imagePath.toString());
    this->imagePaths.push_back(imagePath);
}

// Saves the image sequence to a video.
void randar::Camcorder::toVideo(const std::string& filename)
{

}

// Listens for new frames to capture.
void randar::Camcorder::onCanvasPresent()
{
    Image image = this->canvas().image();
    this->push(image);
}

// Node.js helper for intuitive image sequence creation.
randar::Camcorder randar::camcorder()
{
    return randar::Camcorder();
}
