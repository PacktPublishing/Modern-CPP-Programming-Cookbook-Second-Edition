#pragma once

#include <iostream>
#include <random>
#include <chrono>
#include <functional>
#include <map>
#include <iomanip>
#include <algorithm>

namespace recipe_2_03
{
   void generate_and_print(
      std::function<int(void)> gen,
      int const iterations = 10000)
   {
      // map to store the numbers and  their repetition
      auto data = std::map<int, int>{};

      // generate random numbers
      for (auto n = 0; n < iterations; ++n)
         ++data[gen()];

      // find the element with the most repetitions
      auto max = std::max_element(
         std::begin(data), std::end(data),
         [](auto kvp1, auto kvp2) {return kvp1.second < kvp2.second; });

      // print the bars
      for (auto i = max->second / 200; i > 0; --i)
      {
         for (auto kvp : data)
         {
            std::cout
               << std::fixed << std::setprecision(1) << std::setw(3)
               << (kvp.second / 200 >= i ? (char)219 : ' ');
         }

         std::cout << '\n';
      }

      // print the numbers
      for (auto kvp : data)
      {
         std::cout
            << std::fixed << std::setprecision(1) << std::setw(3)
            << kvp.first;
      }

      std::cout << '\n';
   }

   void execute()
   {
      {
         auto mtgen = std::mt19937{};

         for (auto i = 0; i < 10; ++i)
         {
            std::cout << mtgen() << '\n';
         }
      }

      {
         auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
         auto mtgen = std::mt19937{ static_cast<unsigned int>(seed) };

         for (auto i = 0; i < 10; ++i)
         {
            std::cout << mtgen() << '\n';
         }
      }

      {
         std::random_device rd;
         auto mtgen = std::mt19937{ rd() };

         for (auto i = 0; i < 10; ++i)
         {
            std::cout << mtgen() << '\n';
         }
      }

      {
         std::random_device rd{};
         auto mtgen = std::mt19937{ rd() };
         auto ud = std::uniform_int_distribution<>{ 1, 6 };

         generate_and_print(
            [&mtgen, &ud]() {return ud(mtgen); });
      }

      {
         std::random_device rd{};
         auto mtgen = std::mt19937{ rd() };
         auto nd = std::normal_distribution<>{ 5, 2 };

         generate_and_print(
            [&mtgen, &nd]() {return static_cast<int>(std::round(nd(mtgen))); });
      }
   }
}