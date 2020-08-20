#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"

TEST_CASE("case1")
{
   SECTION("function1")
   {
      REQUIRE(true);
   }
}

TEST_CASE("case2")
{
   SECTION("function2")
   {
      REQUIRE(false);
   }
}