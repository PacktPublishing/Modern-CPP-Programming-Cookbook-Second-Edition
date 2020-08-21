#pragma once

#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <numeric>
#include <memory>

namespace recipe_3_02
{
   using namespace std::string_literals;

   namespace v1
   {
      struct foo
      {
         int         id;
         std::string name;

         auto run()
         {
            return [i = id, n = name] { std::cout << i << ' ' << n << '\n'; };
         }
      };
   }

   namespace v2
   {
      struct foo
      {
         int         id;
         std::string name;

         auto run()
         {
            // warning when compiled with c++20
            return [=] { std::cout << id << ' ' << name << '\n'; };
         }
      };
   }

   namespace v3
   {
      struct foo
      {
         int         id;
         std::string name;

         auto run()
         {
            return[this] { std::cout << id << ' ' << name << '\n'; };
         }
      };
   }

   inline bool is_positive(int const n)
   {
      return n > 0;
   }

   class range_selector
   {
      int minimum_;
      int maximum_;
   public:
      explicit range_selector(int const minimum, int const maximum) :
         minimum_(minimum), maximum_(maximum)
      {
      }

      bool operator()(int const n)
      {
         return minimum_ <= n && n <= maximum_;
      }
   };

   struct __lambda_name__
   {
      bool operator()(int const n) const { return n > 0; }
   };

   class __lambda_name_2__
   {
      int minimum_;
      int maximum_;
   public:
      explicit __lambda_name_2__(int const minimum, int const maximum) :
         minimum_(minimum), maximum_(maximum)
      {}

      __lambda_name_2__(const __lambda_name_2__&) = default;
      __lambda_name_2__(__lambda_name_2__&&) = default;
      __lambda_name_2__& operator=(const __lambda_name_2__&) = delete;
      ~__lambda_name_2__() = default;

      bool operator() (int const n) const
      {
         return minimum_ <= n && n <= maximum_;
      }
   };

   void execute()
   {
      auto numbers = std::vector<int>{ 0, 2, -3, 5, -1, 6, 8, -4, 9 };
      auto texts = std::vector<std::string>{ "hello"s, " "s, "world"s, "!"s };

      {
         auto positives = std::count_if(std::begin(numbers), std::end(numbers),
            is_positive);

         std::cout << "positives: " << positives << '\n';

         auto minimum{ 5 }; // could be an input params
         auto maximum{ 10 };
         auto inrange = std::count_if(std::begin(numbers), std::end(numbers),
            range_selector(minimum, maximum));

         std::cout << "inrange(5, 10): " << inrange << '\n';
      }

      {
         auto positives = std::count_if(std::begin(numbers), std::end(numbers),
            [](int const n) {return n > 0; });

         std::cout << "positives: " << positives << '\n';

         auto minimum{ 5 };
         auto maximum{ 10 };
         auto inrange = std::count_if(
            std::begin(numbers), std::end(numbers),
            [minimum, maximum](int const n) {return minimum <= n && n <= maximum; });

         std::cout << "inrange(5, 10): " << inrange << '\n';
      }

      {
         auto sum = std::accumulate(std::begin(numbers), std::end(numbers), 0,
            [](int const s, int const n) {return s + n; });

         std::cout << "sum: " << sum << '\n';

         auto text = std::accumulate(std::begin(texts), std::end(texts), ""s,
            [](std::string const s, std::string const n) {return s + n; });

         std::cout << "text: " << text << '\n';
      }

      // generalized lambda captures
      {
         auto ptr = std::make_unique<int>(42);
         auto l = [lptr = std::move(ptr)](){return ++*lptr; };
      }

      {
         auto l = v3::foo{ 42, "john" }.run();
         l(); // does not print 42 john
      }
   }
}
