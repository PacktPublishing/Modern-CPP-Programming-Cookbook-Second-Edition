#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

#ifdef USE_RANGES_V3
#include "range/v3/view.hpp"
#include "range/v3/algorithm/sort.hpp"
#include "range/v3/algorithm/copy.hpp"
#include "range/v3/algorithm/reverse.hpp"
#include "range/v3/algorithm/count_if.hpp"
#include "range/v3/algorithm/max.hpp"

namespace rv = ranges::views;
namespace rg = ranges;

template<class T>
struct ranges_ostream_iterator : std::ostream_iterator<T>
{
   using std::ostream_iterator<T>::ostream_iterator;
   ranges_ostream_iterator() : std::ostream_iterator<T>{ std::cout } {}
   ranges_ostream_iterator& operator++() { std::ostream_iterator<T>::operator++(); return *this; }
   ranges_ostream_iterator& operator++(int) { return operator++(); }
   using difference_type = int;
   int operator-(ranges_ostream_iterator const&) { return 0; }
};

#define OSTREAM_ITERATOR ranges_ostream_iterator

#else
#include <ranges>

namespace rv = std::ranges::views;
namespace rg = std::ranges;

#define OSTREAM_ITERATOR std::ostream_iterator
#endif


bool is_prime(int const number)
{
   if (number != 2)
   {
      if (number < 2 || number % 2 == 0) return false;
      auto root = std::sqrt(number);
      for (int i = 3; i <= root; i += 2)
      {
         if (number % i == 0) return false;
      }
   }
   return true;
}

int main()
{
   // ------------ views --------------

   // print numbers from 1 to 9
   // 1 2 3 4 5 6 7 8 9
   for (auto i : rv::iota(1, 10))
   {
      std::cout << i << ' ';
   }
   std::cout << '\n';

   // print all primes from 1 to 99
   // 2 3 5 7 11 13 17 19 23 29 31 37 41 43 47 53 59 61 67 71 73 79 83 89 97
   for (auto i : rv::iota(1, 100) |
                 rv::filter(is_prime))
   {
      std::cout << i << ' ';
   }
   std::cout << '\n';

   // print all primes from a sequence of numbers
   // 2 3 5 13
   std::vector<int> nums{ 1, 1, 2, 3, 5, 8, 13, 21 };
#ifdef USE_RANGES_V3
   for (auto i : rv::all(nums) | rv::filter(is_prime))
#else
   for (auto i : nums | rv::filter(is_prime))
#endif
   {
      std::cout << i << ' ';
   }
   std::cout << '\n';

   // print the successor of all primes from 1 to 99
   // 3 4 6 8 12 14 18 20 24 30 32 38 42 44 48 54 60 62 68 72 74 80 84 90 98
   for (auto i : rv::iota(1, 100) |
                 rv::filter(is_prime) |
                 rv::transform([](int const n) {return n + 1; }))
   {
      std::cout << i << ' ';
   }
   std::cout << '\n';

   // print the first 10 primes from 1 to 99
   // 2 3 5 7 11 13 17 19 23 29
   for (auto i : rv::iota(1, 100) |
                 rv::filter(is_prime) |
                 rv::take(10))
   {
      std::cout << i << ' ';
   }
   std::cout << '\n';

   // print the first 10 primes from 99 to 1
   // 97 89 83 79 73 71 67 61 59 53
   for (auto i : rv::iota(1, 100) |
                 rv::reverse |
                 rv::filter(is_prime) |
                 rv::take(10))
   {
      std::cout << i << ' ';
   }
   std::cout << '\n';

   // print the last 10 primes from 1 to 99
   // 53 59 61 67 71 73 79 83 89 97
   for (auto i : rv::iota(1, 100) |
                 rv::reverse |
                 rv::filter(is_prime) |
                 rv::take(10) |
                 rv::reverse)
   {
      std::cout << i << ' ';
   }
   std::cout << '\n';

   // print the primes between 1 and 99 skipping the first and last 10
   // 31 37 41 43 47
   for (auto i : rv::iota(1, 100) |
                 rv::filter(is_prime) |
                 rv::drop(10) |
                 rv::reverse |
                 rv::drop(10) |
                 rv::reverse)
   {
      std::cout << i << ' ';
   }
   std::cout << '\n';


   // --------- algorithms ---------    
   std::vector<int> v{ 5, 2, 7, 1, 4, 2, 9, 5 };

   // 9
   std::cout << rg::max(v) << '\n';

   // 1 2 2 4 5 5 7 9
   rg::sort(v);
   rg::copy(v, OSTREAM_ITERATOR<int>(std::cout, " "));
   std::cout << '\n';

   // 9 7 5 5 4 2 2 1
   rg::reverse(v);
   rg::copy(v, OSTREAM_ITERATOR<int>(std::cout, " "));
   std::cout << '\n';

   // 5
   std::cout << rg::count_if(v, is_prime) << '\n';
}