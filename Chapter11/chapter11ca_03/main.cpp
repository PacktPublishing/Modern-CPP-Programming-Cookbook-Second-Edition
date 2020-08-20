#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "..\testlib\point3d.h"

void function_that_throws()
{
   throw std::runtime_error("error");
}

void function_no_throw()
{
}

class OnTheLine : public Catch::MatcherBase<point3d>
{
   point3d const p1;
   point3d const p2;
public:
   OnTheLine(point3d const & p1, point3d const & p2):
      p1(p1), p2(p2)
   {
   }

   virtual bool match(point3d const & p) const override
   {
      auto rx = p2.x() - p1.x() != 0 ? (p.x() - p1.x()) / (p2.x() - p1.x()) : 0;
      auto ry = p2.y() - p1.y() != 0 ? (p.y() - p1.y()) / (p2.y() - p1.y()) : 0;
      auto rz = p2.z() - p1.z() != 0 ? (p.z() - p1.z()) / (p2.z() - p1.z()) : 0;

      return 
         Approx(rx).epsilon(0.01) == ry &&
         Approx(ry).epsilon(0.01) == rz;
   }

protected:
   virtual std::string describe() const
   {
      std::ostringstream ss;
      ss << "on the line between " << p1 << " and " << p2;
      return ss.str();
   }
};

inline OnTheLine IsOnTheLine(
   point3d const & p1, 
   point3d const & p2)
{
   return OnTheLine {p1, p2};
}

TEST_CASE("assertions")
{
   SECTION("basic")
   {
      int a = 42;
      CHECK(a == 42);
      REQUIRE(a == 42);

      auto expr = a < 10 || a %2 == 0;
      REQUIRE(expr);
   }
   SECTION("basic false")
   {
      int a = 42;
      CHECK_FALSE(a > 100);
      REQUIRE_FALSE(a > 100);
   }
   SECTION("floating point")
   {
      double a = 42.5;
      CHECK(42.0 == Approx(a).epsilon(0.02));
      REQUIRE(42.0 == Approx(a).epsilon(0.02));
   }
   SECTION("expressions")
   {
      CHECK_NOTHROW(function_no_throw());
      REQUIRE_NOTHROW(function_no_throw());

      CHECK_THROWS(function_that_throws());
      REQUIRE_THROWS(function_that_throws());

      CHECK_THROWS_AS(function_that_throws(), std::runtime_error);
      REQUIRE_THROWS_AS(function_that_throws(), std::runtime_error);

      CHECK_THROWS_WITH(function_that_throws(), "error");
      REQUIRE_THROWS_WITH(function_that_throws(), Catch::Matchers::Contains("error"));
   }
   SECTION("matchers")
   {
      std::string text = "this is an example";
      CHECK_THAT(
         text,
         Catch::Matchers::Contains("EXAMPLE", Catch::CaseSensitive::No));
      REQUIRE_THAT(
         text,
         Catch::Matchers::StartsWith("this") &&
         Catch::Matchers::Contains("an"));
   }
}

TEST_CASE("matchers")
{
   SECTION("point origin")
   {
      point3d p { 2,2,2 };
      REQUIRE_THAT(p, IsOnTheLine(point3d{ 0,0,0 }, point3d{3,3,3}));
   }
}