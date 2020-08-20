#pragma once

#include <iostream>
#include <algorithm>
#include <execution>
#include <assert.h>

namespace recipe_8_11
{
   template <typename Time = std::chrono::microseconds,
      typename Clock = std::chrono::high_resolution_clock>
      struct perf_timer
   {
      template <typename F, typename... Args>
      static Time duration(F&& f, Args... args)
      {
         auto start = Clock::now();

         std::invoke(std::forward<F>(f), std::forward<Args>(args)...);

         auto end = Clock::now();

         return std::chrono::duration_cast<Time>(end - start);
      }
   };

   template <typename Iter, typename F>
   void parallel_map(Iter begin, Iter end, F f)
   {
      std::transform(
         std::execution::par,
         begin, end,
         begin,
         std::forward<F>(f));
   }

   template <typename Iter, typename R, typename F>
   auto parallel_reduce(Iter begin, Iter end, R init, F op)
   {
      return std::reduce(
         std::execution::par,
         begin, end,
         init,
         std::forward<F>(op));
   }

   void execute()
   {
      std::vector<int> v(5000000);
      std::iota(std::begin(v), std::end(v), 1);

      auto v1 = v;
      auto s1 = 0LL;

      auto t11 = perf_timer<>::duration([&] {
         std::transform(std::begin(v1), std::end(v1), std::begin(v1),
            [](int const i) {return i + i; }); });
      auto t12 = perf_timer<>::duration([&] {
         s1 = std::accumulate(std::begin(v1), std::end(v1), 0LL,
            std::plus<>()); });

      auto v2 = v;
      auto s2 = 0LL;
      auto t21 = perf_timer<>::duration([&] {
         parallel_map(std::begin(v2), std::end(v2),
            [](int const i) {return i + i; }); });
      auto t22 = perf_timer<>::duration([&] {
         s2 = parallel_reduce(std::begin(v2), std::end(v2), 0LL,
            std::plus<>()); });

      assert(v1 == v2);
      assert(s1 == s2);

      std::cout << "sequential sum: " << s1 << '\n';
      std::cout << "parallel sum 1: " << s2 << '\n';

      std::cout << "sequential" << '\n';
      std::cout << "  map:    "
         << std::chrono::duration<double, std::milli>(t11).count()
         << "ms" << '\n';
      std::cout << "  reduce: "
         << std::chrono::duration<double, std::milli>(t12).count()
         << "ms" << '\n';

      std::cout << "parallel" << '\n';
      std::cout << "  map:    "
         << std::chrono::duration<double, std::milli>(t21).count()
         << "ms" << '\n';
      std::cout << "  reduce: "
         << std::chrono::duration<double, std::milli>(t22).count()
         << "ms" << '\n';

      auto v5 = v;
      auto s5 = 0LL;

      auto t52 = perf_timer<>::duration([&] {
         s5 = std::transform_reduce(
            std::begin(v5), std::end(v5),
            0LL,
            std::plus<>(),
            [](int const i) {return i + i; }
         ); });

      auto v6 = v;
      auto s6 = 0LL;

      auto t62 = perf_timer<>::duration([&] {
         s6 = std::transform_reduce(
            std::execution::par,
            std::begin(v6), std::end(v6),
            0LL,
            std::plus<>(),
            [](int const i) {return i + i; }
         ); });

      assert(s5 == s6);

      std::cout << "sequential sum (tr): " << s5 << '\n';
      std::cout << "parallel sum (tr)  : " << s6 << '\n';

      std::cout << "sequential (tr)    :"
         << std::chrono::duration<double, std::milli>(t52).count()
         << "ms" << '\n';
      std::cout << "parallel (tr)      :"
         << std::chrono::duration<double, std::milli>(t62).count()
         << "ms" << '\n';

   }
}