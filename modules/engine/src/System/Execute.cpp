#include <cstdlib>
#include <stdexcept>
#include <randar/System/Execute.hpp>

// Executes a command on the system.
int randar::execute(std::string command)
{
    int cmd = std::system(command.c_str());
    if (cmd < 0) {
        throw std::runtime_error("Execution failed: " + command);
    }

    if (!WIFEXITED(cmd)) {
        throw std::runtime_error("Abnormal exit: " + command);
    }

    return WEXITSTATUS(cmd);
}
