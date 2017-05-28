#include <randar/System/Execute.hpp>

// Executes a command on the system.
int randar::execute(const std::string& command)
{
    std::string discardedOutput;
    return randar::execute(command, discardedOutput);
}

int randar::execute(const std::string& command, std::string& output)
{
    output = "";
    char outputBuffer[128];

    // Execute command.
    FILE *fp = ::popen(command.c_str(), "r");
    if (fp == nullptr) {
        throw std::runtime_error("Failed to open pipe: " + command);
    }

    // Get output.
    while (::fgets(outputBuffer, 128, fp) != nullptr) {
        output += std::string(outputBuffer);
    }

    // Close pipe, check exit code.
    int code = ::pclose(fp);
    if (code == -1) {
        throw std::runtime_error("Failed to execute command: " + command);
    }

    return code;
}
