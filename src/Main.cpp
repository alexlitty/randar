#ifdef _WIN32
#include <Windows.h>
#endif

#include <randar/Ui/Ui.hpp>

#if !(defined (__linux__) || defined (_WIN32))
#error "Unable to detect target platform. Specify __linux__ or _WIN32 as a preprocessor directive."
#endif

int main(int argc, char *argv[])
{
    // Check basic platform requirements.
    if (CHAR_BIT != 8) {
        throw std::runtime_error(
            "Randar must be ran on a platform with 8-bit bytes."
        );
    }

    if (sizeof(float) != 4) {
        throw std::runtime_error(
            "Randar must be ran on a platform with 32-bit floats."
        );
    }

#if defined (__linux__)
	::CefMainArgs arguments(argc, argv);
#elif defined (_WIN32)
	::CefMainArgs arguments(::GetModuleHandle(NULL));
#endif

    // This process may be spawned by CEF for special browser processing. If
    // that is the case, this function will handle whatever CEF needs. Otherwise
    // the program continues.
    randar::Browser browser;
    int exitCode = browser.executeProcess(arguments);
    if (exitCode != -1) {
        return exitCode;
    }

    // Prepare Randar as an interface.
    randar::seedRandomWithTime();
    randar::Ui ui(browser);

    // Run Randar.
    ui.run();
    return 0;
}
