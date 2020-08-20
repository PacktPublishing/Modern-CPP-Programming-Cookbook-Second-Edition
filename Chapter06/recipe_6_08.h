#pragma once

#include <variant>
#include <iostream>
#include <string>
#include <vector>
#include <type_traits>
#include <iomanip>
#include <chrono>

namespace recipe_6_08
{
   using namespace std::string_literals;

   struct foo
   {
      int value;

      explicit foo(int const i) : value(i) {}
   };

   void execute()
   {
      {
         std::variant<int, double, std::string> v;
         v = 42;   // v contains int 42
         v = 42.0; // v contains double 42.0
         v = "42"; // v contains string "42"
      }

      {
         std::variant<int, double, std::string> v = 42;

         auto i1 = std::get<int>(v);
         auto i2 = std::get<0>(v);

         try
         {
            auto f = std::get<double>(v);
         }
         catch (std::bad_variant_access const & e)
         {
            std::cout << e.what() << '\n'; // Unexpected index
         }
      }

      {
         std::variant<int, double, std::string> v = 42;
         static_assert(std::variant_size_v<decltype(v)> == 3);
         std::cout << "index = " << v.index() << '\n';
         v = 42.0;
         std::cout << "index = " << v.index() << '\n';
         v = "42";
         std::cout << "index = " << v.index() << '\n';
      }

      {
         std::variant<int, double, std::string> v = 42;
         std::cout << "int? " << std::boolalpha << std::holds_alternative<int>(v) << '\n'; // int? true

         v = "42";
         std::cout << "int? " << std::boolalpha << std::holds_alternative<int>(v) << '\n'; // int? false
      }

      {
         std::variant<int, std::string, foo> v = 42;
         v.emplace<foo>(42);
      }

      {
         //std::variant<foo, int> v; // error

         std::variant<std::monostate, foo, int> v; // error
         v = 42;       // v contains int 42
         std::cout << std::get<int>(v) << '\n';
         v = foo{ 42 }; // v contains foo{42}
         std::cout << std::get<foo>(v).value << '\n';
      }

      {
         std::variant<int, double, std::string> v = 42;
         std::visit([](auto&& arg) {std::cout << arg << '\n'; }, v);
         v = 42.0;
         std::visit([](auto&& arg) {std::cout << arg << '\n'; }, v);

#ifdef CONSTEXPR_IF_AVAILABLE
         std::visit([](auto&& arg) {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, int>) std::cout << "int " << arg << '\n';
            else if constexpr (std::is_same_v<T, double>) std::cout << "double " << arg << '\n';
            else if constexpr (std::is_same_v<T, std::string>) std::cout << "std::string " << arg << '\n';
         }, v);
#endif
      }
   }
}