#pragma once

#include <vector>
#include <string>
#include <algorithm>
#include <utility>

namespace recipe_3_03
{
   using namespace std::string_literals;

   struct __lambda_name__
   {
      template<typename T1, typename T2>
      auto operator()(T1 const s, T2 const n) const { return s + n; }

      __lambda_name__(const __lambda_name__&) = default;
      __lambda_name__(__lambda_name__&&) = default;
      __lambda_name__& operator=(const __lambda_name__&) = delete;
      ~__lambda_name__() = default;
   };

   struct foo
   {
      static void f() { std::cout << "foo\n"; }
   };

   template <typename ...T>
   void foobar(T&& ... args)
   { /* ... */
   }

   void execute()
   {
      auto numbers = std::vector<int>{ 0, 2, -3, 5, -1, 6, 8, -4, 9 };
      auto texts = std::vector<std::string>{ "hello"s, " "s, "world"s, "!"s };
      
      // with non-generic lambdas
      {
         auto sum = std::accumulate(std::begin(numbers), std::end(numbers), 0,
            [](int const s, int const n) {return s + n; });

         auto text = std::accumulate(std::begin(texts), std::end(texts), ""s,
            [](std::string const s, std::string const n) {return s + n; });
      }

      // with generic lambdas
      {
         auto lsum = [](auto const s, auto const n) {return s + n; };

         auto sum = std::accumulate(std::begin(numbers), std::end(numbers),
            0, lsum);

         auto text = std::accumulate(std::begin(texts), std::end(texts),
            ""s, lsum);
      }

      // C++17 lambda
      {
         auto tl = [](auto x)
         {
            using T = std::decay_t<decltype(x)>;
            T other;
            T::f();
         };

         tl(foo{});
      }

      {
         auto tl = [](auto&& ...args)
         {
            return foobar(std::forward<decltype(args)>(args)...);
         };

         tl(1, 42.99, "lambda");
      }

      // C++20 template lambdas
      {
         std::vector<int> vi{ 1, 1, 2, 3, 5, 8 };
         auto tl = []<typename T>(std::vector<T> const& vec)
         {
            std::cout << std::size(vec) << '\n';
         };

         tl(vi); // OK, prints 6
         //tl(42); // error
      }

      {
         auto tl = []<typename T>(T x, T y)
         {
            std::cout << x << ' ' << y << '\n';
         };

         tl(10, 20); // OK
         //tl(10, "20"); // error
      }

      {
         auto tl = []<typename T>(T x)
         {
            T other;
            T::f();
         };

         tl(foo{});
      }

      {
         auto tl = []<typename ...T>(T && ...args)
         {
            return foobar(std::forward<T>(args)...);
         };

         tl(1, 42.99, "lambda");
      }
   }

}
