#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include "recipe_5_10.h"

namespace recipe_5_11
{
   using namespace std::string_literals;

   template <typename F, typename C>
   void process(F&& f, C const & c)
   {
      std::for_each(std::begin(c), std::end(c), std::forward<F>(f));
   }

   void execute()
   {
      std::vector<int> v1{ 1, 2, 3, 4, 5 };
      for (auto i = std::begin(v1); i != std::end(v1); ++i)
         std::cout << *i << '\n';

      std::vector<int> v2;
      std::copy(std::cbegin(v1), std::cend(v1), std::back_inserter(v2));

      int a[5] = { 1, 2, 3, 4, 5 };
      auto pos = std::find_if(std::crbegin(a), std::crend(a), 
                              [](int const n) {return n % 2 == 0; });

      recipe_5_10::dummy_array<std::string, 5> sa;
      recipe_5_10::dummy_array<int, 5> sb;
      sa[0] = "1"s;
      sa[1] = "2"s;
      sa[2] = "3"s;
      sa[3] = "4"s;
      sa[4] = "5"s;      

      std::transform(
         std::begin(sa), std::end(sa), 
         std::begin(sb), 
         [](std::string const & s) {return std::stoi(s); });

      auto l = [](auto const e) {std::cout << e << '\n'; };
      process(l, v1);
      process(l, a);
      process(l, sa);
   }
}