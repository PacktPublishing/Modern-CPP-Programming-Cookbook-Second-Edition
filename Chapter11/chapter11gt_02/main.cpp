#include <gtest/gtest.h>
#include "..\testlib\point3d.h"

TEST(TestConstruction, TestConstructor)
{
   auto p = point3d{ 1,2,3 };
   ASSERT_EQ(p.x(), 1);
   ASSERT_EQ(p.x(), 2);
   ASSERT_EQ(p.x(), 3);
}

TEST(TestConstruction, TestOrigin)
{
   auto p = point3d::origin();
   ASSERT_EQ(p.x(), 0);
   ASSERT_EQ(p.x(), 0);
   ASSERT_EQ(p.x(), 0);
}

TEST(TestMethods, TestOffset)
{
   auto p = point3d{ 1,2,3 };
   p.offset(1, 1, 1);
   ASSERT_TRUE(p.x() == 2);
   ASSERT_TRUE(p.y() == 3);
   ASSERT_TRUE(p.z() == 3); // will fail
}

TEST(TestOperations, TestEqual)
{
   auto p1 = point3d{ 1,2,3 };
   auto p2 = point3d{ 1,2,3 };
   auto p3 = point3d{ 3,2,1 };

   ASSERT_EQ(p1, p2);
   ASSERT_EQ(p1, p3);
}

TEST(TestOperations, TestNotEqual)
{
   auto p1 = point3d{ 1,2,3 };
   auto p2 = point3d{ 3,2,1 };

   ASSERT_NE(p1, p2);
}

TEST(TestOperations, TestLess)
{
   auto p1 = point3d{ 1,2,3 };
   auto p2 = point3d{ 1,2,3 };
   auto p3 = point3d{ 3,2,1 };

   ASSERT_FALSE(p1 < p2);
   ASSERT_LT(p1, p3);
}

TEST(TestConstruction, DISABLED_TestConversionConstructor) 
{ /* ... */ }

TEST(DISABLED_TestComparisons, TestEquality) 
{ /* ... */ }
TEST(DISABLED_TestComparisons, TestInequality)
{ /* ... */ }

int main(int argc, char **argv)
{
   ::testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}
