#include <randar/Log/LogMessage.hpp>

// Constructs an "info" level log message.
randar::LogMessage::LogMessage(const std::string& initContents)
: contents(initContents)
{

}

// Constructs a log message with a specified level.
randar::LogMessage::LogMessage(
    const std::string& initLevel,
    const std::string& initContents
) :
  level(initLevel),
  contents(initContents)
{

}

// Converts this log message to JSON.
Json randar::LogMessage::toJson() const
{
    return {
        { "level", this->level },
        { "contents", this->contents }
    };
}

// Converts this log message to a user-friendly string.
std::string randar::LogMessage::toString() const
{
    return "[" + this->level + "] " + this->contents;
}

randar::LogMessage::operator std::string() const
{
    return this->toString();
}
