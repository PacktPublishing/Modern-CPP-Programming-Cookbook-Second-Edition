#define BOOST_TEST_NO_MAIN
#define BOOST_TEST_ALTERNATIVE_INIT_API
#include <boost/test/included/unit_test.hpp>
#include <iostream>

BOOST_AUTO_TEST_CASE(first_test_function)
{
   int a = 42;
   BOOST_TEST(a > 0);
}

bool custom_init_unit_test()
{
   std::cout << "test runner custom init" << std::endl;
   return true;
}

int main(int argc, char* argv[])
{
   return boost::unit_test::unit_test_main(custom_init_unit_test, argc, argv);
}