#define BOOST_TEST_MODULE Testing point 3d
#include <boost/test/included/unit_test.hpp>
#include "..\testlib\point3d.h"

BOOST_AUTO_TEST_SUITE(test_construction)

BOOST_AUTO_TEST_CASE(test_constructor)
{
   auto p = point3d{ 1,2,3 };
   BOOST_TEST(p.x() == 1);
   BOOST_TEST(p.y() == 2);
   BOOST_TEST(p.z() == 4); // will fail
}

BOOST_AUTO_TEST_CASE(test_origin)
{
   auto p = point3d::origin();
   BOOST_TEST(p.x() == 0);
   BOOST_TEST(p.y() == 0);
   BOOST_TEST(p.z() == 0);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(test_operations)

BOOST_AUTO_TEST_SUITE(test_methods)

BOOST_AUTO_TEST_CASE(test_offset)
{
   auto p = point3d{ 1,2,3 };
   p.offset(1, 1, 1);
   BOOST_TEST(p.x() == 2);
   BOOST_TEST(p.y() == 3);
   BOOST_TEST(p.z() == 3); // will fail
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(test_operations)

BOOST_AUTO_TEST_SUITE(test_operators)

BOOST_AUTO_TEST_CASE(
   test_equal, 
   *boost::unit_test::description("test operator==")
   *boost::unit_test::label("opeq"))
{
   auto p1 = point3d{ 1,2,3 };
   auto p2 = point3d{ 1,2,3 };
   auto p3 = point3d{ 3,2,1 };

   BOOST_TEST(p1 == p2);
   BOOST_TEST(p1 == p3); // will fail
}

BOOST_AUTO_TEST_CASE(test_not_equal, 
   *boost::unit_test::description("test operator!=")
   *boost::unit_test::label("opeq")
   *boost::unit_test::depends_on("test_operations/test_operators/test_equal"))
{
   auto p1 = point3d{ 1,2,3 };
   auto p2 = point3d{ 3,2,1 };

   BOOST_TEST(p1 != p2);
}

BOOST_AUTO_TEST_CASE(test_less)
{
   auto p1 = point3d{ 1,2,3 };
   auto p2 = point3d{ 1,2,3 };
   auto p3 = point3d{ 3,2,1 };

   BOOST_TEST(!(p1 < p2));
   BOOST_TEST(p1 < p3);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
