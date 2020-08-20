#pragma once

#include <string>
#include <memory>
#include <vector>
#include <map>
#include <iostream>

namespace recipe_1_01
{
   using namespace std::string_literals;

   class foo
   {
      int x_;
   public:
      foo(int const x = 0) :x_{ x } {}
      int& get() { return x_; }
   };

   auto proxy_get(foo& f) { return f.get(); }

   decltype(auto) proxy_get2(foo& f) { return f.get(); }

   struct
   {
      template<typename T, typename U>
      auto operator () (T const a, U const b) const { return a + b; }
   } L;

   void execute()
   {
      {
         auto i = 42;				            // int
         auto d = 42.5;				            // double
         auto s = "text";				         // const char*
         auto b = new char[10]{ 0 };		   // char*
         auto p = std::make_shared<int>(42);	// std::shared_ptr<int>
         auto v = { 1, 2, 3 };			      // std::initializer_list<int>
         auto l = [](char const c) {return toupper(c); }; // int(char)
      }

      {
         auto s = std::string{ "text" };		   // std::string
         auto v = std::vector<int>{ 1, 2, 3 };	// std::vector<int>
      }

      {
         auto v = std::vector<int>{ 1, 2, 3 };
         int size1 = v.size();	// implicit conversion, possible loss of data
         auto size2 = v.size();
         //auto size3 = int{ v.size() }; // error, narrowing conversion
      }

      {
         std::map<int, std::string> m;

         for (std::map<int, std::string>::const_iterator it = m.cbegin();
            it != m.cend();
            ++it)
         {
         }

         for (auto it = m.cbegin(); it != m.cend(); ++it)
         {
         }
      }

      {
         foo f(42);
         auto x = f.get();
         x = 100;
         std::cout << f.get() << '\n'; // prints 42
      }

      {
         auto l1 = long long{ 42 }; // error

         using llong = long long;
         auto l2 = llong{ 42 };     // OK
         auto l3 = 42LL;            // OK
      }

      {
         auto f = foo{ 42 };
         //auto& x = proxy_get(f); // cannot convert from 'int' to 'int &'
      }

      {
         auto f = foo{ 42 };
         decltype(auto) x = proxy_get2(f);
      }

      {
         auto ladd = [](auto const a, auto const b) { return a + b; };

         auto i = ladd(40, 2);            // 42
         auto s = ladd("forty"s, "two"s); // "fortytwo"s
      }
   }

   auto func1(int const i) -> int
   {
      return 2 * i;
   }

   auto func2(int const i)
   {
      return 2 * i;
   }
}