#ifndef RANDAR_LOG_LOG_HPP
#define RANDAR_LOG_LOG_HPP

#include <set>
#include <randar/Log/LogMessage.hpp>

namespace randar
{
    class LogListener;

    /**
     * A log, which receives messages and reports them to listeners.
     */
    class Log
    {
        std::set<LogListener*> listeners;

    public:
        /**
         * Adds a new log listener, which will be notified when a new message
         * is logged.
         */
        void addListener(LogListener* listener);

        /**
         * Removes a log listener.
         */
        void removeListener(LogListener* listener);

        /**
         * Logs a generic message.
         */
        void log(const std::string& level, const std::string& contents);

        /**
         * Logs an informational message.
         */
        void info(const std::string& contents);

        /**
         * Logs an error message.
         */
        void error(const std::string& contents);
    };
}

#endif
