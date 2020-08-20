#pragma once

#include <iostream>

namespace recipe_9_02
{
   void func_no_throw() noexcept
   {
   }

   template <typename T>
   T generic_func_1() noexcept(std::is_nothrow_constructible_v<T>)
   {
      return T{};
   }

   template <typename T>
   T generic_func_2() noexcept(noexcept(T{}))
   {
      return T{};
   }

   template <typename F, typename A>
   auto func(F&& f, A&& arg) noexcept
   {
      static_assert(noexcept(f(arg)), "F is throwing!");
      return f(arg);
   }

   int double_it(int const i) noexcept
   {
      return i + i;
   }

   int half_it(int const i)
   {
      throw std::runtime_error("not implemented!");
   }

   struct foo
   {
      foo() {}
   };

   void execute()
   {
      std::cout << std::boolalpha
         << noexcept(func_no_throw()) << '\n'                // true
         << noexcept(generic_func_1<int>()) << '\n'          // true
         << noexcept(generic_func_1<std::string>()) << '\n'  // true
         << noexcept(generic_func_2<int>()) << '\n'          // true
         << noexcept(generic_func_2<std::string>()) << '\n'  // true
         << noexcept(generic_func_2<foo>()) << '\n'          // false
         << noexcept(double_it(42)) << '\n'                  // true
         << noexcept(half_it(42)) << '\n'                    // false
         << noexcept(func(double_it, 42)) << '\n';           // true
   }
}