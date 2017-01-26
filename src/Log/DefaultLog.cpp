#include <randar/Log/DefaultLog.hpp>

randar::Log& randar::getDefaultLog()
{
    static Log defaultLog;
    return defaultLog;
}
