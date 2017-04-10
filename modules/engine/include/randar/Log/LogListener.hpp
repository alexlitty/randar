#ifndef RANDAR_LOG_LOG_LISTENER_HPP
#define RANDAR_LOG_LOG_LISTENER_HPP

#include <randar/Log/DefaultLog.hpp>

namespace randar
{
    /**
     * Handler for log messages.
     */
    class LogListener
    {
        Log& log;

    public:
        /**
         * Constructs this log listener, adding it to a specified log.
         *
         * If a log is not specified, this listener is added to the default log.
         */
        LogListener(Log& initLog = randar::getDefaultLog());

        /**
         * Destructs this log listener, removing it from its associated log.
         */
        ~LogListener();

        /**
         * Called when the associated log receives a message.
         */
        virtual void onLog(const LogMessage& message) = 0;
    };
}

#endif
