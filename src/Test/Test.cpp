#define CATCH_CONFIG_RUNNER
#include <randar/Test/Test.hpp>

// Runs all available test suites.
void randar::test()
{
    Catch::Session session;
    session.run();
}
