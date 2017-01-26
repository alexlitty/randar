#ifndef RANDAR_LOG_LOG_MESSAGE_HPP
#define RANDAR_LOG_LOG_MESSAGE_HPP

#include <randar/Utility/Json.hpp>

namespace randar
{
    struct LogMessage
    {
        const std::string level;
        const std::string contents;

        /**
         * Constructs an "info" level log message.
         */
        LogMessage(const std::string& initContents);

        /**
         * Constructs a log message with a specified level.
         *
         * The name of the level is arbitrary, but it makes most sense to use
         * "info" or "error".
         */
        LogMessage(
            const std::string& initLevel,
            const std::string& initContents
        );

        /**
         * Converts this log message to JSON.
         */
        Json toJson() const;

        /**
         * Converts this log message to a user-friendly string.
         */
        std::string toString() const;
        operator std::string() const;
    };
}

#endif
