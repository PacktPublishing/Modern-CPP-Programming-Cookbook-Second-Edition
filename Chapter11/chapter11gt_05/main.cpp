#include <gtest/gtest.h>

TEST(Sample, Test)
{
   auto a = 42;
   ASSERT_EQ(a, 0);
}

int main(int argc, char **argv)
{
   ::testing::InitGoogleTest(&argc, argv);

   return RUN_ALL_TESTS();
}
