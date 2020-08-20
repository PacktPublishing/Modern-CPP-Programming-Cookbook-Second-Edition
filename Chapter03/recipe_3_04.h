#pragma once

#include <functional>
#include <iostream>

namespace recipe_3_04
{
   constexpr int fib(int const n)
   {
      return n <= 2 ? 1 : fib(n - 1) + fib(n - 2);
   }

   std::function<int(int const)> fib_create()
   {
      std::function<int(int const)> lfib = [&lfib](int const n)
      {
         return n <= 2 ? 1 : lfib(n - 1) + lfib(n - 2);
      };

      return lfib;
   }

   std::function<int(int const)> fib_create2()
   {
      std::function<int(int const)> f = [](int const n) 
      {
         std::function<int(int const)> lfib = [&lfib](int n)
         {
            return n <= 2 ? 1 : lfib(n - 1) + lfib(n - 2);
         };
         return lfib(n);
      };

      return f;
   }

   void execute()
   {
      {
         auto f10 = fib(10);

         std::cout << "fib(10): " << f10 << '\n';
      }

      {
         std::function<int(int const)> lfib = [&lfib](int const n)
         {
            return n <= 2 ? 1 : lfib(n - 1) + lfib(n - 2);
         };

         auto f10 = lfib(10);

         std::cout << "fib(10): " << f10 << '\n';
      }

      {
         auto lfib = fib_create2();

         // auto f10 = lfib(10); // crash
      }

      {
         auto lfib = fib_create2();

         auto f10 = lfib(10);

         std::cout << "fib(10): " << f10 << '\n';
      }
   }
}
