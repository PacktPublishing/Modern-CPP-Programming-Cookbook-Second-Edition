#pragma once

#include <string>
#include <iostream>
#include <algorithm>

namespace recipe_5_05
{
   using namespace std::string_literals;

   inline bool IsPrime(int const number)
   {
      if (((!(number & 1)) && number != 2) || (number < 2) || (number % 3 == 0 && number != 3))
         return (false);

      for (int k = 1; 36 * k*k - 12 * k < number; ++k)
         if ((number % (6 * k + 1) == 0) || (number % (6 * k - 1) == 0))
            return (false);

      return true;
   }

   void execute()
   {
      {
         std::vector<int> v{ 1, 1, 2, 3, 5, 8, 13 };

         auto it = std::find(v.cbegin(), v.cend(), 3);
         if (it != v.cend()) std::cout << *it << '\n';
      }

      {
         std::vector<int> v{ 1, 1, 2, 3, 5, 8, 13 };

         auto it = std::find_if(v.cbegin(), v.cend(), [](int const n) {return n > 10; });
         if (it != v.cend()) std::cout << *it << '\n';
      }

      {
         std::vector<int> v{ 1, 1, 2, 3, 5, 8, 13 };

         auto it = std::find_if_not(v.cbegin(), v.cend(), [](int const n) {return n % 2 == 1; });
         if (it != v.cend()) std::cout << *it << '\n';
      }

      {
         std::vector<int> v1{ 1, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 1 };
         std::vector<int> v2{ 1, 0, 1 };

         auto it = std::find_end(
            v1.cbegin(), v1.cend(),
            v2.cbegin(), v2.cend());

         if (it != v1.cend())
            std::cout << "found at index "
            << std::distance(v1.cbegin(), it) << '\n';
      }

      {
         std::vector<int> v{ 1, 1, 2, 3, 5, 8, 13 };
         std::vector<int> p{ 5, 7, 11 };

         auto it = std::find_first_of(
            v.cbegin(), v.cend(),
            p.cbegin(), p.cend());

         if (it != v.cend())
            std::cout << "found " << *it
            << " at index " << std::distance(v.cbegin(), it)
            << '\n';
      }

      {
         auto text = "The quick brown fox jumps over the lazy dog"s;
         auto word = "over"s;

         auto it = std::search(
            text.cbegin(), text.cend(),
            word.cbegin(), word.cend());

         if (it != text.cend())
            std::cout << "found " << word
            << " at index " << std::distance(text.cbegin(), it)
            << '\n';
      }

      {
#ifdef SEARCHERS_AVAILABLE
         auto text = "The quick brown fox jumps over the lazy dog"s;
         auto word = "over"s;

         auto it = std::search(
            text.cbegin(), text.cend(),
            std::make_boyer_moore_searcher(word.cbegin(), word.cend()));

         if (it != text.cend())
            std::cout << "found " << word
            << " at index " << std::distance(text.cbegin(), it)
            << '\n';
#endif
      }

      {
         std::vector<int> v{ 1, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 1 };

         auto it = std::search_n(v.cbegin(), v.cend(), 2, 0);

         if (it != v.cend())
            std::cout << "found at index " << std::distance(v.cbegin(), it)
            << '\n';
      }

      {
         std::vector<int> v{ 1, 1, 2, 3, 5, 8, 13 };

         auto it = std::adjacent_find(v.cbegin(), v.cend());
         if (it != v.cend())
            std::cout << "found at index " << std::distance(v.cbegin(), it)
            << '\n';
      }

      {
         std::vector<int> v{ 1, 1, 2, 3, 5, 8, 13 };

         auto it = std::adjacent_find(
            v.cbegin(), v.cend(),
            [](int const a, int const b) {return IsPrime(a) && IsPrime(b); });

         if (it != v.cend())
            std::cout << "found at index " << std::distance(v.cbegin(), it)
            << '\n';
      }

      {
         std::vector<int> v{ 1, 1, 2, 3, 5, 8, 13 };

         auto success = std::binary_search(v.cbegin(), v.cend(), 8);

         if (success) std::cout << "found" << '\n';
      }

      {
         std::vector<int> v{ 1, 1, 2, 3, 5, 8, 13 };

         auto it = std::lower_bound(v.cbegin(), v.cend(), 1);

         if (it != v.cend())
            std::cout << "lower bound at "
            << std::distance(v.cbegin(), it)
            << '\n';
      }

      {
         std::vector<int> v{ 1, 1, 2, 3, 5, 8, 13 };

         auto it = std::upper_bound(v.cbegin(), v.cend(), 1);

         if (it != v.cend())
            std::cout << "upper bound at "
            << std::distance(v.cbegin(), it)
            << '\n';
      }

      {
         std::vector<int> v{ 1, 1, 2, 3, 5, 8, 13 };

         auto bounds = std::equal_range(v.cbegin(), v.cend(), 1);

         std::cout << "range between indexes "
            << std::distance(v.cbegin(), bounds.first)
            << " and "
            << std::distance(v.cbegin(), bounds.second)
            << '\n';
      }
   }
}