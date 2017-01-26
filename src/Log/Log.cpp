#include <randar/Log/Log.hpp>
#include <randar/Log/LogListener.hpp>

// Adds a new log listener, which will be notified when a new message is logged.
void randar::Log::addListener(randar::LogListener* listener)
{
    this->listeners.insert(listener);
}

// Removes a log listener.
void randar::Log::removeListener(randar::LogListener* listener)
{
    this->listeners.erase(listener);
}

// Logs a generic message.
void randar::Log::log(const std::string& level, const std::string& contents)
{
    LogMessage message(level, contents);

    for (auto listener : this->listeners) {
        listener->onLog(message);
    }
}

// Logs an informational message.
void randar::Log::info(const std::string& contents)
{
    this->log("info", contents);
}

// Logs an error message.
void randar::Log::error(const std::string& contents)
{
    this->log("error", contents);
}
