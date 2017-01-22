#include <randar/Ui/Ui.hpp>

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

    // This process may be spawned by CEF for special browser processing. If
    // that is the case, this function will handle whatever CEF needs. Otherwise
    // the program continues.
    randar::Browser browser;
    int exitCode = browser.executeProcess(::CefMainArgs(argc, argv));
    if (exitCode != -1) {
        return exitCode;
    }

    // Prepare Randar.
    randar::seedRandomWithTime();

    // Run Randar with an interface.
    randar::Ui ui(browser);
    ui.run();
    return 0;
}
