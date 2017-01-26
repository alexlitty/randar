#include <randar/Log/LogListener.hpp>

// Constructor.
randar::LogListener::LogListener(randar::Log& initLog)
: log(initLog)
{
    this->log.addListener(this);
}

// Destructor.
randar::LogListener::~LogListener()
{
    this->log.removeListener(this);
}
