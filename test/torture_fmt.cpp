#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Basic torture-fmt test", "[torture-fmt]") {
    REQUIRE(1 + 1 == 2);
}
