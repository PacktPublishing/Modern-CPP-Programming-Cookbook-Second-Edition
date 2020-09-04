#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
/*
TEST_CASE("first_test_case", "[learn][catch]")
{
   SECTION("first_test_function")
   {
      auto i{ 42 };
      REQUIRE(i == 42);
   }
}
*/
SCENARIO("first_scenario", "[learn][catch]")
{
   GIVEN("an integer")
   {
      auto i = 0;
      WHEN("assigned a value")
      {
         i = 42;
         THEN("the value can be read back")
         {
            REQUIRE(i == 42);
         }
      }
   }
}