#include <gtest/gtest.h>

TEST(TestAssertions, Basic)
{
   EXPECT_TRUE(2 + 2 == 2 * 2);
   EXPECT_FALSE(1 == 2);

   ASSERT_TRUE(2 + 2 == 2 * 2);
   ASSERT_FALSE(1 == 2);
}

TEST(TestAssertions, Binary)
{
   auto a = 42, b = 10;
   EXPECT_EQ(a, 42);
   EXPECT_NE(a, b);
   EXPECT_LT(b, a);
   EXPECT_LE(b, 11);
   EXPECT_GT(a, b);
   EXPECT_GE(b, 10);

   ASSERT_EQ(a, 42);
   ASSERT_NE(a, b);
   ASSERT_LT(b, a);
   ASSERT_LE(b, 11);
   ASSERT_GT(a, b);
   ASSERT_GE(b, 10);
}

TEST(TestAssertions, Strings)
{
   auto str = "sample";
   EXPECT_STREQ(str, "sample");
   EXPECT_STRNE(str, "simple");
   EXPECT_STRCASEEQ(str, "SAMPLE");
   EXPECT_STRCASENE(str, "SIMPLE");

   ASSERT_STREQ(str, "sample");
   ASSERT_STRNE(str, "simple");
   ASSERT_STRCASEEQ(str, "SAMPLE");
   ASSERT_STRCASENE(str, "SIMPLE");
}

TEST(TestAssertions, FloatingPoint)
{
   EXPECT_FLOAT_EQ(1.9999999f, 1.9999998f);
   ASSERT_FLOAT_EQ(1.9999999f, 1.9999998f);
}

void function_that_throws()
{
   throw std::runtime_error("error");
}

void function_no_throw()
{

}

TEST(TestAssertions, Exceptions)
{
   EXPECT_THROW(function_that_throws(), std::runtime_error);
   EXPECT_ANY_THROW(function_that_throws());
   EXPECT_NO_THROW(function_no_throw());

   ASSERT_THROW(function_that_throws(), std::runtime_error);
   ASSERT_ANY_THROW(function_that_throws());
   ASSERT_NO_THROW(function_no_throw());
}

bool is_positive(int const val)
{
   return val != 0;
}

bool is_double(int const val1, int const val2)
{
   return val2 + val2 == val1;
}

TEST(TestAssertions, Predicates)
{
   EXPECT_PRED1(is_positive, 42);
   EXPECT_PRED2(is_double, 42, 21);

   ASSERT_PRED1(is_positive, 42);
   ASSERT_PRED2(is_double, 42, 21);
}

TEST(TestAssertions, Fails)
{
   ADD_FAILURE();
   ADD_FAILURE_AT(__FILE__, __LINE__);
}

int main(int argc, char **argv)
{
   ::testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}
