#include <randar/Filesystem/Directory.hpp>
#include <randar/Test/Test.hpp>

TEST_CASE("binary streams")
{
    auto file = randar::Directory::Temp.getFile("randar.bin");

    REQUIRE(1 == 1);
}
