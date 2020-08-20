#pragma once

#include <vector>
#include <iostream>
#include <algorithm>
#include <map>

namespace recipe_1_08
{
   std::vector<int> getRates()
   {
      return std::vector<int> {1, 1, 2, 3, 5, 8, 13};
   }

   void print_rate(int const rate)
   {
      std::cout << rate << '\n';
   }

   std::multimap<int, bool> getRates2()
   {
      return std::multimap<int, bool>
      {
         { 1, true },
         { 1, true },
         { 2, false },
         { 3, true },
         { 5, true },
         { 8, false },
         { 13, true }
      };
   }

   void execute()
   {
      {
         auto rates = getRates();

         // using iterators
         for (auto it = rates.begin(); it != rates.end(); ++it)
         {
            std::cout << *it << '\n';
         }

         // using an index
         for (size_t i = 0; i < rates.size(); ++i)
         {
            std::cout << rates[i] << '\n';
         }
      }

      {
         auto rates = getRates();

         std::for_each(rates.begin(), rates.end(), print_rate);

         std::for_each(rates.begin(), rates.end(), [](auto const rate) {std::cout << rate << '\n'; });
      }

      {
         auto rates = getRates();
         for (int rate : rates)
         {
            std::cout << rate << '\n';
         }

         for(int& rate : rates)
         {
            rate *= 2;
         }

         for (auto&& rate : getRates())
         {
            std::cout << rate << '\n';
         }

         for (auto & rate : rates)
         {
            rate *= 2;
         }

         for (auto const & rate : rates)
         {
            std::cout << rate << '\n';
         }
      }

      {
         for (auto&& kvp : getRates2())
         {
            std::cout << kvp.first << '\n';
         }

         for (auto&& kvp : getRates2())
         {
            bool flag;
            int rate;
            std::tie(rate, flag) = kvp;

            std::cout << rate << '\n';
         }

         for (auto&&[rate, flag] : getRates2())
         {
            std::cout << rate << '\n';
         }
      }
   }
}