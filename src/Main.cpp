#include <randar/Ui/Ui.hpp>

int main(int argc, char *argv[])
{
    randar::Browser browser;

    // This process may be spawned by CEF for special browser processing. If
    // that is the case, this function will handle whatever CEF needs. Otherwise
    // the program continues.
    int exitCode = browser.executeProcess(::CefMainArgs(argc, argv));
    if (exitCode != -1) {
        return exitCode;
    }

    // Prepare Randar.
    randar::seedRandomWithTime();

    // Run Randar with an interface.
    randar::Ui ui(browser);
    ui.execute();
    return 0;
}
