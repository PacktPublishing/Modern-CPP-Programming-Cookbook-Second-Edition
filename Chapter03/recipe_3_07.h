#pragma once

#include <vector>
#include <list>
#include <map>
#include <array>
#include <queue>
#include <string>
#include <algorithm>
#include <iostream>
#include <cmath>
#include "funclib.h"

namespace recipe_3_07
{
   using namespace std::string_literals;

   template<class T = double>
   struct fround
   {
      typename std::enable_if_t<std::is_floating_point_v<T>, T>
      operator()(const T& value) const
      {
         return std::round(value);
      }
   };

   void execute()
   {
      {
         auto vnums = std::vector<int>{ 0, 2, -3, 5, -1, 6, 8, -4, 9 };
         auto r = funclib::mapf([](int const i) {return std::abs(i); }, vnums);
         // r = {0, 2, 3, 5, 1, 6, 8, 4, 9}

         auto lnums = std::list<int>{ 1, 2, 3, 4, 5 };
         auto l = funclib::mapf([](int const i) {return i*i; }, lnums);
         // l = {1, 4, 9, 16, 25}

         auto amounts = std::array<double, 5> {10.42, 2.50, 100.0, 23.75, 12.99};
         auto a = funclib::mapf(fround<>(), amounts);
         // a = {10.0, 3.0, 100.0, 24.0, 13.0}

         auto words = std::map<std::string, int>{ { "one", 1 },{ "two", 2 },{ "three", 3 } };
         auto m = funclib::mapf(
            [](std::pair<std::string, int> const kvp)
         {
            return std::make_pair(funclib::mapf(toupper, kvp.first), kvp.second);
         },
            words);
         // m = { {"ONE", 1}, {"TWO", 2}, {"THREE", 3} }

         auto priorities = std::queue<int>();
         priorities.push(10);
         priorities.push(20);
         priorities.push(30);
         priorities.push(40);
         priorities.push(50);
         auto p = funclib::mapf([](int const i) {return i > 30 ? 2 : 1; }, priorities);
         // p = {1, 1, 1, 2, 2}
      }

      {
         auto vnums = std::vector<int>{ 0, 2, -3, 5, -1, 6, 8, -4, 9 };
         auto s1 = funclib::foldl([](const int s, const int n) {return s + n; }, vnums, 0); // s1 = 22
         auto s2 = funclib::foldl(std::plus<>(), vnums, 0); // s2 = 22

         auto s3 = funclib::foldr([](const int s, const int n) {return s + n; }, vnums, 0); // s3 = 22
         auto s4 = funclib::foldr(std::plus<>(), vnums, 0); // s4 = 22

         auto texts = std::vector<std::string>{ "hello"s, " "s, "world"s, "!"s };
         auto txt1 = funclib::foldl([](std::string const & s, std::string const & n) {return s + n; }, texts, ""s);
         // txt1 = "hello world!"
         auto txt2 = funclib::foldr([](std::string const & s, std::string const & n) {return s + n; }, texts, ""s);
         // txt2 = "!world hello"

         char chars[] = { 'c','i','v','i','c' };
         auto str1 = funclib::foldl(std::plus<>(), chars, ""s); // str1 = "civic"
         auto str2 = funclib::foldr(std::plus<>(), chars, ""s); // str2 = "civic"

         auto words = std::map<std::string, int>{ { "one", 1 },{ "two", 2 },{ "three", 3 } };
         auto count = funclib::foldl(
            [](int const s, std::pair<std::string, int> const kvp) {return s + kvp.second; },
            words,
            0);

         auto q = std::queue<int>{};
         q.push(1);
         q.push(2);
         q.push(3);
         q.push(4);
         q.push(5);
         auto sum = funclib::foldl(std::plus<>(), q, 0); // sum = 15
      }

      {
         auto vnums = std::vector<int>{ 0, 2, -3, 5, -1, 6, 8, -4, 9 };

         auto s = funclib::foldl(
            std::plus<>(),
            funclib::mapf(
               [](int const i) {return i+i; }, 
               funclib::mapf(
                  [](int const i) {return std::abs(i); },
                  vnums)),
            0); 
         // s = 76
      }
   }
}
