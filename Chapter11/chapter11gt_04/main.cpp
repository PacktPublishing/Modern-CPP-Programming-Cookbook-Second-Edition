#include <gtest/gtest.h>
#include <vector>
#include <numeric>

class TestFixture : public ::testing::Test
{
protected:
   TestFixture()
   {
      std::cout << "constructing fixture" << std::endl;

      data.resize(10);
      std::iota(std::begin(data), std::end(data), 1);
   }

   ~TestFixture()
   {
      std::cout << "destroying fixture" << std::endl;
   }

protected:
   std::vector<int> data;
};

TEST_F(TestFixture, TestData)
{
   ASSERT_EQ(data.size(), 10);
   ASSERT_EQ(data[0], 1);
   ASSERT_EQ(data[data.size()-1], data.size());
}

class TestEnvironment : public ::testing::Environment
{
public:
   virtual void SetUp() override 
   {
      std::cout << "environment setup" << std::endl;
   }

   virtual void TearDown() override 
   {
      std::cout << "environment cleanup" << std::endl;
   }

   int n{ 42 };
};

int main(int argc, char **argv)
{
   ::testing::InitGoogleTest(&argc, argv);
   ::testing::AddGlobalTestEnvironment(new TestEnvironment{});

   return RUN_ALL_TESTS();
}
