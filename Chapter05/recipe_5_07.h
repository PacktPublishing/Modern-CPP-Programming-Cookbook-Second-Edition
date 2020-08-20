#pragma once

#include <vector>
#include <algorithm>
#include <numeric>
#include <random>

namespace recipe_5_07
{
   void execute()
   {
      {
         std::vector<int> v(5);
         std::fill(v.begin(), v.end(), 42);
         // v = {42, 42, 42, 42, 42}

         std::array<int, 5> a;
         std::fill(a.begin(), a.end(), 42);
         // a = {42, 42, 42, 42, 42}
      }

      {
         std::vector<int> v(10);
         std::fill_n(v.begin(), 5, 42);
         // v = {42, 42, 42, 42, 42, 0, 0, 0, 0, 0}
      }

      {
         std::random_device rd{};
         std::mt19937 mt{ rd() };
         std::uniform_int_distribution<> ud{1, 10};

         std::vector<int> v(5);

         std::generate(v.begin(), v.end(), [&ud, &mt] {return ud(mt); });         
      }

      {
         std::vector<int> v(5);

         auto i = 1;
         std::generate_n(v.begin(), v.size(), [&i] { return i*i++; });
         // v = {1, 4, 9, 16, 25}
      }

      {
         std::vector<int> v(5);
         
         std::iota(v.begin(), v.end(), 1);
         // v = {1, 2, 3, 4, 5}
      }
   }
}