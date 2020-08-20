#pragma once

#include <iostream>
#include <limits>
#include <bitset>

namespace recipe_2_02
{
   int minimum(int const * const start, int const * const end)
   {
      int minval = INT_MAX;
      for (int const * p = start; p != end; ++p)
      {
         if (*p < minval)
            minval = *p;
      }
      return minval;
   }

   template<typename T, typename Iter>
   T minimum(Iter const start, Iter const end)
   {
      T minval = std::numeric_limits<T>::max();
      for (auto i = start; i < end; ++i)
      {
         if (*i < minval)
            minval = *i;
      }
      return minval;
   }

   template <typename T>
   void print_type_properties()
   {
      std::cout
         << "min=" << std::numeric_limits<T>::min() << '\n'
         << "max=" << std::numeric_limits<T>::max() << '\n'
         << "bits=" << std::numeric_limits<T>::digits << '\n'
         << "decdigits=" << std::numeric_limits<T>::digits10 << '\n'
         << "integral=" << std::numeric_limits<T>::is_integer << '\n'
         << "signed=" << std::numeric_limits<T>::is_signed << '\n'
         << "exact=" << std::numeric_limits<T>::is_exact << '\n'
         << "infinity=" << std::numeric_limits<T>::has_infinity << '\n';
   }

   int get_value()
   {
      return 0;
   }

   void execute()
   {
      print_type_properties<unsigned short>();
      print_type_properties<double>();
      print_type_properties<int>();

      int range[std::numeric_limits<char>::max() + 1] = { 0 };

      switch (get_value())
      {
      case std::numeric_limits<int>::min():
         break;
      }

      auto n = 42;
      std::bitset<std::numeric_limits<decltype(n)>::digits> bits{ static_cast<unsigned long long>(n) };
   }
}