#pragma once

#include <string>
#include <iostream>

using namespace std::string_literals;

namespace recipe_4_04
{
   template <typename T>
   void func(typename T::value_type const a) 
      { std::cout << "func<>" << '\n'; }
   void func(int const a) 
      { std::cout << "func" << '\n'; }

   template <typename T>
   struct some_type
   {
      using value_type = T;
   };

   template <typename T,
             typename = typename std::enable_if<std::is_standard_layout_v<T>, T>::type>
   class pod_wrapper
   {
      T value;
   };


   template <typename T,
             typename = typename std::enable_if_t<std::is_standard_layout_v<T>, T>>
   class pod_wrapper2
   {
      T value;
   };

   struct point
   {
      int x;
      int y;
   };

   template<typename T,
            typename = typename std::enable_if_t<std::is_integral_v<T>, T>>
   auto mul(T const a, T const b)
   {
      return a * b;
   }

   template <typename Test, typename T = void>
   using EnableIf = typename std::enable_if_t<Test::value, T>;

   template <typename Test, typename T = void>
   using DisableIf = typename std::enable_if_t<!Test::value, T>;

   template <typename T, typename = EnableIf<std::is_standard_layout<T>>>
   class pod_wrapper3
   {
      T value;
   };

   template<typename T, typename = EnableIf<std::is_integral<T>>>
   auto mul2(T const a, T const b)
   {
      return a * b;
   }

   template <typename T>
   auto compute(T const a, T const b)
   {
      static_assert(std::is_integral<T>, "An integral type expected");
      return a + b;
   }

   template <typename T, typename = void>
   auto compute(T const a, T const b)
   {
      static_assert(!std::is_integral<T>, "A non-integral type expected");
      return a * b;
   }

   template <typename T, typename = EnableIf<std::is_integral<T>>>
   auto compute2(T const a, T const b)
   {
      return a * b;
   }

   template <typename T, typename = DisableIf<std::is_integral<T>>,
      typename = void>
      auto compute2(T const a, T const b)
   {
      return a + b;
   }

   void execute()
   {
      {
         func(42);
         func<some_type<int>>(42);
         //func("string"s); // error
      }

      {
         [[maybe_unused]] pod_wrapper2<int> w1;
         [[maybe_unused]] pod_wrapper2<point> w2;
         //pod_wrapper2<std::string> w3; // error
      }

      {
         auto v1 = mul(1, 2);     // OK
         //auto v2 = mul(1.0, 2.0); // error: no matching overloaded function found
      }

      {
         [[maybe_unused]] pod_wrapper3<int> w1;
         [[maybe_unused]] pod_wrapper3<point> w2;
         //pod_wrapper3<std::string> w3; // error
      }

      {
         auto v1 = mul2(1, 2);     // OK
         //auto v2 = mul2(1.0, 2.0); // error: no matching overloaded function found
      }

      {
         //auto v1 = compute(1, 2); // error: ambiguous call to overloaded function
         //auto v2 = compute(1.0, 2.0); // error: ambiguous call to overloaded function
      }

      {
         auto v1 = compute2(1, 2);     // v1 = 2
         auto v2 = compute2(1.0, 2.0); // v2 = 3.0
      }
   }
}