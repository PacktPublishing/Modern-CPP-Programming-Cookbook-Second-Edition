#include <gtest/gtest.h>

TEST(FirstTestSuite, FirstTest)
{
   int a = 42;
   ASSERT_TRUE(a > 0);
}

int main(int argc, char **argv)
{
   ::testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}
