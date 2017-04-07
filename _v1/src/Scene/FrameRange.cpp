#include <stdexcept>
#include <randar/Scene/FrameRange.hpp>

// Constructor.
randar::FrameRange::FrameRange(const Frame& initStart, const Frame& initEnd)
: start(initStart),
  end(initEnd)
{
    this->check();
}

randar::FrameRange::FrameRange(const Frame& frame)
: start(frame),
  end(frame)
{

}

// Validates this range.
void randar::FrameRange::check() const
{
    if (this->start == randar::Frame::Final) {
        throw std::logic_error("FrameRange starts with Final Frame");
    }

    if (this->start > this->end) {
        throw std::logic_error("FrameRange start is beyond end");
    }
}

// Sets the range of frames.
void randar::FrameRange::set(const randar::Frame& newStart, const randar::Frame& newEnd)
{
    this->start = newStart;
    this->end = newEnd;
    this->check();
}

void randar::FrameRange::setStart(const Frame& newStart)
{
    this->start = newStart;
    this->check();
}

void randar::FrameRange::setEnd(const Frame& newEnd)
{
    this->end = newEnd;
    this->check();
}

// Gets the range of frames.
randar::Frame randar::FrameRange::getStart() const
{
    return this->start;
}

randar::Frame randar::FrameRange::getEnd() const
{
    return this->end;
}

// Retrieves the number of frames in this range.
uint32_t randar::FrameRange::count() const
{
    return (this->end.get() - this->start.get()) + 1;
}

// Checks whether a frame is contained by this range.
bool randar::FrameRange::contains(const Frame& other)
{
    return (this->start <= other) && (this->end >= other);
}
