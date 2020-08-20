#pragma once

#include <map>
#include <iostream>
#include <mutex>
#include <algorithm>

namespace std {
   template <class T>
   pair(T&&, char const*)->pair<T, std::string>;

   template <class T>
   pair(char const*, T&&)->pair<std::string, T>;

   pair(char const*, char const*)->pair<std::string, std::string>;
}

namespace recipe_1_14
{
   template <class T>
   struct foo
   {
      foo(T v) :data(v) {}
   private:
      T data;
   };

   template <typename T>
   constexpr foo<T> make_foo(T&& value)
   {
      return foo{ value };
   }

   void execute()
   {      
      {
         std::pair<int, char const*> p{ 42, "demo" };
         std::vector<int>            v{ 1, 2 };
         foo<int>                    f{ 42 };
      }
      {
         auto f = make_foo(42);
      }

      {
         std::pair   p{ 42, "demo" };  // deduces std::pair<int, char const*>
         std::vector v{ 1, 2 };        // deduces std::vector<int>
         std::less   l;                // deduces std::less<void>
      }

      {
         auto f = new foo(42);
      }

      {
         std::mutex mx;

         // deduces std::lock_guard<std::mutex>
         auto lock = std::lock_guard(mx);

         std::vector<int> v;
         // deduces std::back_insert_iterator<std::vector<int>>
         std::fill_n(std::back_insert_iterator(v), 5, 42);
      }

      {
         std::pair  p1{ 42, "demo" };    // std::pair<int, std::string>
         std::pair  p2{ "demo", 42 };    // std::pair<std::string, int>
         std::pair  p3{ "42", "demo" };  // std::pair<std::string, std::string>
      }

      {
         // std::pair<>    p1{ 42, "demo" }; // ERROR
         // std::pair<int> p2{ 42, "demo" }; // ERROR
      }
   }
}