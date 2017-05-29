#include <randar/Render/Canvas.hpp>
#include <randar/Render/Camcorder.hpp>
#include <randar/System/Directory.hpp>
#include <randar/System/Execute.hpp>

// Constructors.
randar::Camcorder::Camcorder()
{

}

randar::Camcorder::Camcorder(randar::Canvas& canvas)
{
    this->watch(canvas);
}

// Assignment.
randar::Camcorder::Camcorder(const randar::Camcorder& other)
{
    *this = other;
}

randar::Camcorder& randar::Camcorder::operator =(const randar::Camcorder& other)
{
    if (other.isWatching()) {
        this->watch(other.canvas());
        this->_imagesDirectory = other._imagesDirectory;
        this->imagePaths = other.imagePaths;
    }

    return *this;
}

randar::Camcorder::Camcorder(randar::Camcorder&& other)
{
    *this = other;
    other.unwatch();
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

    if (this->_imagesDirectory.toString() == ".") {
        this->_imagesDirectory = randar::tempDirectory();
    }

    randar::Path imagePath = this->_imagesDirectory.child(basename);
    image.save(imagePath.toString());
    this->imagePaths.push_back(imagePath);
}

// Counts the images in the sequence.
uint32_t randar::Camcorder::count() const
{
    return this->imagePaths.size();
}

// Saves the image sequence to a video.
void randar::Camcorder::save(const randar::Path& filepath)
{
    uint16_t fps = this->canvas().fps();
    if (!fps) {
        fps = 24;
    }

    randar::createDirectory(filepath.parent());
    randar::Path imageWildcard = this->_imagesDirectory.child("%8d.png");

    std::string cmd = std::string("ffmpeg")
                    + " -y"
                    + " -r " + std::to_string(fps)
                    + " -start_number 0"
                    + " -i " + imageWildcard.toString()
                    + " -c:v libx264"
                    + " -vf \"fps=24,format=yuv420p\""
                    + " " + filepath.toString();

    std::string output;
    if (randar::execute(cmd, output)) {
        std::string msg = "Failed to generate video";
        if (!output.empty()) {
            msg += ": " + output;
        }
        throw std::runtime_error(msg);
    }
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
