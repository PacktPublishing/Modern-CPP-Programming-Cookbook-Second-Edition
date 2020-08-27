#pragma once

#include <string>

namespace recipe_3_05
{
   template <typename T>
   T sum(T value)
   {
      return value;
   }

   template <typename T, typename... Ts>
   T sum(T head, Ts... tail)
   {
      return head + sum(tail...);
   }

   template <typename F, typename T1, typename T2>
   auto fold(F&& f, T1 v1, T2 v2)
   {
      return f(v1, v2);
   }

   template <typename F, typename T, typename... Ts>
   auto fold(F&& f, T head, Ts... tail)
   {
      return f(head, fold(std::forward<F>(f), tail...));
   }

   template <typename T>
   bool is_fibonacci(T v1, T v2, T v3)
   {
      return v1 + v2 == v3;
   }

   template <typename T>
   bool is_any(T value, T elem)
   {
      return value == elem;
   }

   template <typename T, typename... Ts>
   bool is_any(T value, T first, Ts... rest)
   {
      return value == first || is_any(value, rest...);
   }

   template<typename... T>
   auto make_even_tuple(T... a)
   {
      static_assert(sizeof...(a) % 2 == 0,
         "expected an even number of arguments");
      std::tuple<T...> t{ a... };
      return t;
   }

   void execute()
   {
      using namespace std::string_literals;

      {
         auto n = sum(1, 2, 3, 4, 5);
         auto s = sum("hello"s, " "s, "world"s, "!"s);
      }

      {
         auto n = fold(std::plus<>(), 1, 2, 3, 4, 5);
         auto s = fold(std::plus<>(), "hello"s, " "s, "world"s, "!"s);
      }

      {
         auto i1 = is_any(42, 1, 23, 76, 44, 5);

         auto a = 0;
      }

      {
         auto t1 = make_even_tuple(1, 2, 3, 4); // OK

         // error: expected an even number of arguments
         // auto t2 = make_even_tuple(1, 2, 3);
      }
   }
}