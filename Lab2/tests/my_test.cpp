#include "../Lab2/include/prime_check.h"
#include "catch.hpp"

TEST_CASE( "Checking on primeness", "[number]" ) {
    REQUIRE( prime_check(-100) == false );
    REQUIRE( prime_check(100) == false );
    REQUIRE( prime_check(7) == true );
}
