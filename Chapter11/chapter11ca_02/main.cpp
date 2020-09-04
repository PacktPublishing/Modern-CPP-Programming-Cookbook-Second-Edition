#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "..\testlib\point3d.h"

TEST_CASE("test construction", "[create]")
{
   SECTION("test constructor")
   {
      auto p = point3d{ 1,2,3 };
      REQUIRE(p.x() == 1);
      REQUIRE(p.y() == 2);
      REQUIRE(p.z() == 4);
   }
   SECTION("test origin")
   {
      auto p = point3d::origin();
      REQUIRE(p.x() == 0);
      REQUIRE(p.y() == 0);
      REQUIRE(p.z() == 0);
   }
}

TEST_CASE("test operations", "[modify]")
{
   SECTION("test methods")
   {
      SECTION("test offset")
      {
         auto p = point3d{ 1,2,3 };
         p.offset(1, 1, 1);
         REQUIRE(p.x() == 2);
         REQUIRE(p.y() == 3);
         REQUIRE(p.z() == 3); // will fail
      }
   }
}

TEST_CASE("test operators", "[compare][op]")
{
   SECTION("test equal")
   {
      auto p1 = point3d{ 1,2,3 };
      auto p2 = point3d{ 1,2,3 };
      auto p3 = point3d{ 3,2,1 };

      REQUIRE(p1 == p2);
      REQUIRE(p1 == p3);
   }
   SECTION("test not equal")
   {
      auto p1 = point3d{ 1,2,3 };
      auto p2 = point3d{ 3,2,1 };

      REQUIRE(p1 != p2);
   }
   SECTION("test less")
   {
      auto p1 = point3d{ 1,2,3 };
      auto p2 = point3d{ 1,2,3 };
      auto p3 = point3d{ 3,2,1 };

      REQUIRE(!(p1 < p2));
      REQUIRE(p1 < p3);
   }
}

SCENARIO("modify existing object")
{
   GIVEN("a default constructed point")
   {
      auto p = point3d{};

      REQUIRE(p.x() == 0);
      REQUIRE(p.y() == 0);
      REQUIRE(p.z() == 0);

      WHEN("increased with 1 unit on all dimensions")
      {
         p.offset(1, 1, 1);

         THEN("all coordinates are equal to 1")
         {
            REQUIRE(p.x() == 1);
            REQUIRE(p.y() == 1);
            REQUIRE(p.z() == 1);
         }
      }
   }
}