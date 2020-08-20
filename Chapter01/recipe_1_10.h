#pragma once

#include <map>
#include <iostream>

namespace recipe_1_10
{
   struct foo
   {
      foo() { std::cout << "foo" << '\n'; }
      foo(int const a) { std::cout << "foo(a)" << '\n'; }
      foo(int const a, double const b) { std::cout << "foo(a, b)" << '\n'; }

      operator bool() const { return true; }
   };

   struct foo2
   {
      foo2() { std::cout << "foo" << '\n'; }
      foo2(std::initializer_list<int> l) { std::cout << "foo(l)" << '\n'; }
      foo2(int const a) { std::cout << "foo(a)" << '\n'; }
      foo2(int const a, double const b) { std::cout << "foo(a, b)" << '\n'; }

      operator bool() const { return true; }
   };

   void bar(foo const f)
   {
   }

   enum ItemSizes { DefaultHeight, Large, MaxSize };

   class string_buffer
   {
   public:
      explicit string_buffer()
      {}

      explicit string_buffer(size_t const size)
      {}

      explicit string_buffer(char const* const ptr)
      {}

      explicit operator bool() const { return true; }
      explicit operator char* const () const { return nullptr; }
   };

   struct handle_t
   {
      explicit handle_t(int const h) : handle(h) {}

      explicit operator bool() const { return handle != 0; };
   private:
      int handle;
   };

   void execute()
   {
      {
         foo f1;              // foo
         foo f2{};            // foo

         foo f3(1);           // foo(a)
         foo f4 = 1;          // foo(a)
         foo f5{ 1 };         // foo(a)
         foo f6 = { 1 };      // foo(a)

         foo f7(1, 2.0);      // foo(a, b)
         foo f8{ 1, 2.0 };    // foo(a, b)
         foo f9 = { 1, 2.0 }; // foo(a, b)

         bool flag = f1;
         if (f2) {}
         std::cout << f3 + f4 << '\n';
         if (f5 == f6) {}
      }

      {
         bar({});             // foo()
         bar(1);              // foo(a)
         bar({ 1, 2.0 });     // foo(a, b)
      }

      {
         string_buffer b4 = string_buffer('a');
         string_buffer b5 = static_cast<string_buffer>(MaxSize);
         string_buffer b6 = string_buffer{ "a" };

         string_buffer b7{ 'a' };
         string_buffer b8('a');

         // error
         //std::cout << b4 + b5 << '\n';
         //if (b4 == b5) {}

         std::cout << static_cast<bool>(b4) + static_cast<bool>(b5) << '\n';
         if (static_cast<bool>(b4) == static_cast<bool>(b5)) {}
      }

      {
         auto h = handle_t{ 42 };
         bool ok = static_cast<bool>(h);
         if (h) {}
      }
   }
}