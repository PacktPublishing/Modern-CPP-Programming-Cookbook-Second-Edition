#define BOOST_TEST_MODULE Learning asserts
#include <boost/test/included/unit_test.hpp>
#include <string>
#include <vector>
#include <list>

BOOST_AUTO_TEST_CASE(regular_tests)
{
   int a = 2, b = 4;
   BOOST_TEST(a == b);
   BOOST_TEST(a == b, "not equal");
   BOOST_TEST(4.201 == 4.200);

   std::string s1{ "sample" };
   std::string s2{ "text" };
   BOOST_TEST(s1 == s2, "not equal");

   BOOST_TEST(4.201 == 4.200, boost::test_tools::tolerance(0.001));

   std::vector<int> v{ 1,2,3 };
   std::list<short> l{ 1,2,3 };

   BOOST_TEST(v == l, boost::test_tools::per_element());

   BOOST_TEST((a > 0 ? true : false));

   BOOST_TEST((a > 2 && b < 5));

   BOOST_ERROR("this test will fail");

   BOOST_TEST_WARN(a == 4, "something is not right");

   BOOST_TEST(BOOST_IS_DEFINED(UNICODE));

   BOOST_TEST_REQUIRE(a == 4, "this is critical");   
}