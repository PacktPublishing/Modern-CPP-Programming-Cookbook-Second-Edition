#pragma once

#include <iostream>


namespace recipe_9_04
{
   constexpr unsigned int factorial(unsigned int const n)
   {
      return n > 1 ? n * factorial(n - 1) : 1;
   }

   class point3d
   {
      double x_;
      double y_;
      double z_;
   public:
      constexpr point3d(double const x = 0,
         double const y = 0,
         double const z = 0)
         :x_{ x }, y_{ y }, z_{ z }
      {}

      constexpr double get_x() const { return x_; }
      constexpr double get_y() const { return y_; }
      constexpr double get_z() const { return z_; }
   };

   struct foo
   {
      int a;
      int b;
   };

   struct bar
   {
      int   value;
      int*  ptr;
      constexpr bar() :value{ 0 }, ptr{ nullptr }{}
   };

#ifdef HAS_CONSTINIT

   int f() { return 42; }
   constexpr int g(bool const c) { return c ? 0 : f(); }

   constinit int c = g(true);  // OK
   //constinit int d = g(false); // error: variable does not have a constant initializer

#endif

   void execute()
   {
      {
         constexpr unsigned int size = factorial(6);
         char buffer[size]{ 0 };

         int n;
         std::cout << "enter factorial value: ";
         std::cin >> n;
         auto result = factorial(n);
      }

      {
         constexpr point3d p{ 0, 1, 2 };
         constexpr auto x = p.get_x();
      }

      {
         static constexpr int c = 42;
         constexpr int const * p = &c;

         static constexpr int const & r = c;
      }

      {
         // zero initialization
         std::string text {};  // zero-initialized to unspecified value
         double arr[10];       // zero-initialized to ten 0.0
         int* ptr;             // zero-initialized to nullptr
         foo f = foo();        // zero-initialized to a=0, b=0

         // constant initialization
         foo const fc{ 1, 2 }; // const-initialized at runtime
         constexpr bar b;      // const-initialized at compile-time
      }
   }
}