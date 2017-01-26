#ifndef RANDAR_LOG_DEFAULT_LOG_HPP
#define RANDAR_LOG_DEFAULT_LOG_HPP

#include <randar/Log/Log.hpp>

namespace randar
{
    /**
     * Retrieves the default log for this program.
     */
    Log& getDefaultLog();

    /**
     * Creates a generic message on the default log.
     */
    void log(const std::string& level, const std::string& contents);

    /**
     * Creates an informational message on the default log.
     */
    void log(const std::string& contents);
    void logInfo(const std::string& contents);

    /**
     * Creates an error message on the default log.
     */
    void logError(const std::string& contents);
}

#endif
