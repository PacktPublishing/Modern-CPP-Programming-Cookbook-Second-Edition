#pragma once

#include <map>
#include <queue>
#include <algorithm>

namespace funclib
{
   template <typename F, typename R>
   R mapf(F&& f, R r)
   {
      std::transform(std::begin(r), std::end(r), std::begin(r),
         std::forward<F>(f));
      return r;
   }

   template<typename F, typename T, typename U>
   std::map<T, U> mapf(F&& f, std::map<T, U> const & m)
   {
      std::map<T, U> r;
      for (auto const kvp : m)
         r.insert(f(kvp));
      return r;
   }

   template<typename F, typename T>
   std::queue<T> mapf(F&& f, std::queue<T> q)
   {
      std::queue<T> r;
      while (!q.empty())
      {
         r.push(f(q.front()));
         q.pop();
      }
      return r;
   }

   template <typename F, typename R, typename T>
   constexpr T foldl(F&& f, R&& r, T i)
   {
      return std::accumulate(
         std::begin(r), std::end(r),
         std::move(i),
         std::forward<F>(f));
   }

   template <typename F, typename R, typename T>
   constexpr T foldr(F&& f, R&& r, T i)
   {
      return std::accumulate(
         std::rbegin(r), std::rend(r),
         std::move(i),
         std::forward<F>(f));
   }

   template <typename F, typename T>
   constexpr T foldl(F&& f, std::queue<T> q, T i)
   {
      while (!q.empty())
      {
         i = f(i, q.front());
         q.pop();
      }

      return i;
   }

   template <typename F, typename G>
   auto compose(F&& f, G&& g)
   {
      return [=](auto x) { return f(g(x)); };
   }

   template <typename F, typename... R>
   auto compose(F&& f, R&&... r)
   {
      return [=](auto x) {
         return f(compose(r...)(x));
      };
   }
}