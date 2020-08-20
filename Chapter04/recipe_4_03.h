#pragma once

namespace recipe_4_03
{
   struct alignas(8) item
   {
      int      id;
      bool     active;
      double   value;
   };

   template <typename T>
   class pod_wrapper
   {
      static_assert(std::is_standard_layout_v<T>, "POD type expected!");

      T value;
   };

   struct point
   {
      int x;
      int y;
   };

   template<typename T>
   auto mul(T const a, T const b)
   {
      static_assert(std::is_integral_v<T>, "Integral type expected");

      return a * b;
   }

   void execute()
   {
      [[maybe_unused]] pod_wrapper<int>         w1; // OK
      [[maybe_unused]] pod_wrapper<point>       w2; // OK
      //pod_wrapper<std::string> w3; // error: POD type expected

      auto v1 = mul(1, 2);       // OK
      //auto v2 = mul(12.0, 42.5); // error: Integral type expected
   }
}