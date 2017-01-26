#include <randar/Log/DefaultLog.hpp>

// Retrieves the default log for this program.
randar::Log& randar::getDefaultLog()
{
    static Log defaultLog;
    return defaultLog;
}

// Creates a generic message on the default log.
void randar::log(const std::string& level, const std::string& contents)
{
    randar::getDefaultLog().log(level, contents);
}

// Creates an informational message on the default log.
void randar::log(const std::string& contents)
{
    randar::logInfo(contents);
}

void randar::logInfo(const std::string& contents)
{
    randar::getDefaultLog().info(contents);
}

// Creates an error message on the default log.
void randar::logError(const std::string& contents)
{
    randar::getDefaultLog().error(contents);
}
