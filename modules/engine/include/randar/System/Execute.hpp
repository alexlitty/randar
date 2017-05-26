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
     * stdout and stderr are discarded for now. Throws an exception if execution
     * could not occur or the command exits abnormally.
     *
     * Returns the command's exit code.
     */
    int execute(std::string command);
}

#endif
