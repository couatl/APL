#include "../include/prime_check.h"
#include "catch.hpp"

SCENARIO("if number is negative")
{
    GIVEN("negative number")
    {
        int k = -100;
        WHEN("checking on primeness")
        {
            THEN("return false")
            {
                REQUIRE(prime_check(k) == false);
            }
        }
    }
}
SCENARIO("if number is prime")
{
    GIVEN("prime number")
    {
        int k = 7;
        WHEN("checking on primeness")
        {
            THEN("return true")
            {
                REQUIRE(prime_check(k) == true);
            }
        }
    }
}
SCENARIO("if number isn't prime")
{
    GIVEN("not prime number")
    {
        int k = 10200;
        WHEN("checking on primeness")
        {
            THEN("return false")
            {
                REQUIRE(prime_check(k) == false);
            }
        }
    }
}