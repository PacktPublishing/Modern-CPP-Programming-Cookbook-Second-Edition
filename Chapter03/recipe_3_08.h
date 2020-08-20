#pragma once

#include <string>
//#include "recipe_3_05.h"
#include "funclib.h"

namespace recipe_3_08
{  
   template <typename F, typename G>
   auto operator*(F&& f, G&& g)
   {
      return funclib::compose(std::forward<F>(f), std::forward<G>(g));
   }

   template <typename F, typename... R>
   auto operator*(F&& f, R&&... r)
   {
      return funclib::operator*(std::forward<F>(f), r...);
   }

   void execute()
   {
      using namespace funclib;

      auto vnums = std::vector<int>{ 0, 2, -3, 5, -1, 6, 8, -4, 9 };

      {
         auto v = compose(
            [](int const n) {return std::to_string(n); },
            [](int const n) {return n * n; })(-3);

         auto n = compose(
            [](int const n) {return std::to_string(n); },
            [](int const n) {return n * n; },
            [](int const n) {return n + n; },
            [](int const n) {return std::abs(n); })(-3);

         auto s = compose(
            [](std::vector<int> const & v) {
            return foldl(std::plus<>(), v, 0); },
            [](std::vector<int> const & v) {
               return mapf([](int const i) {return i + i; }, v); },
            [](std::vector<int> const & v) {
               return mapf([](int const i) {return std::abs(i); }, v); })(vnums);
      }

      {
         auto n =
            ([](int const n) {return std::to_string(n); } *
             [](int const n) {return n * n; } *
             [](int const n) {return n + n; } *
             [](int const n) {return std::abs(n); })(-3);

         auto c = 
            [](std::vector<int> const & v) {
               return foldl(std::plus<>(), v, 0); } *
            [](std::vector<int> const & v) {
               return mapf([](int const i) {return i + i; }, v); } *
            [](std::vector<int> const & v) {
               return mapf([](int const i) {return std::abs(i); }, v); };

         auto s = c(vnums);
      }
   }
}