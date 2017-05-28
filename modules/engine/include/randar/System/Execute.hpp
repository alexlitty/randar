#ifndef RANDAR_SYSTEM_EXECUTE_HPP
#define RANDAR_SYSTEM_EXECUTE_HPP

#include <cstdlib>
#include <stdexcept>
#include <string>

namespace randar
{
    /**
     * Executes a command on the system.
     *
     * If provided, the output argument is filled with resulting stdout and
     * stderr.
     *
     * Throws an exception if execution could not occur or the command exits
     * abnormally.
     *
     * Returns the command's exit code.
     */
    int execute(const std::string& command);
    int execute(const std::string& command, std::string& output);
}

#endif
