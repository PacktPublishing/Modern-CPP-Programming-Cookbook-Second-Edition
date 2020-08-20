#pragma once

#include <iostream>
#include <algorithm>
#include <thread>
#include <numeric>
#include <chrono>
#include <cassert>

namespace recipe_8_09
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

   unsigned get_no_of_threads()
   {
      return std::thread::hardware_concurrency();
   }


   template <typename Iter, typename F>
   void parallel_map(Iter begin, Iter end, F f)
   {
      auto size = std::distance(begin, end);

      if (size <= 10000)
         std::transform(begin, end, begin, std::forward<F>(f));
      else
      {
         auto no_of_threads = get_no_of_threads();
         auto part = size / no_of_threads;
         auto last = begin;

         std::vector<std::thread> threads;
         for (unsigned i = 0; i < no_of_threads; ++i)
         {
            if (i == no_of_threads - 1)
               last = end;
            else
               std::advance(last, part);

            threads.emplace_back([=, &f] {std::transform(begin, last, begin, std::forward<F>(f)); });

            begin = last;
         }

         for (auto & t : threads) t.join();
      }
   }

   template <typename Iter, typename R, typename F>
   auto parallel_reduce(Iter begin, Iter end, R init, F op)
   {
      auto size = std::distance(begin, end);

      if (size <= 10000)
         return std::accumulate(begin, end, init, std::forward<F>(op));
      else
      {
         auto no_of_threads = get_no_of_threads();
         auto part = size / no_of_threads;
         auto last = begin;

         std::vector<std::thread> threads;
         std::vector<R> values(no_of_threads);
         for (unsigned i = 0; i < no_of_threads; ++i)
         {
            if (i == no_of_threads - 1)
               last = end;
            else
               std::advance(last, part);

            threads.emplace_back([=, &op](R& result) {result = std::accumulate(begin, last, R{}, std::forward<F>(op)); },
               std::ref(values[i]));

            begin = last;
         }

         for (auto & t : threads) t.join();

         return std::accumulate(std::begin(values), std::end(values), init, std::forward<F>(op));
      }
   }

   void test_mapreduce_threads()
   {
      std::vector<int> sizes
      {
         10000, 100000, 500000, 
         1000000, 2000000, 5000000, 
         10000000, 25000000, 50000000
      };

      std::cout
         << std::right << std::setw(8) << std::setfill(' ') << "size"
         << std::right << std::setw(8) << "s map"
         << std::right << std::setw(8) << "p map"
         << std::right << std::setw(8) << "s fold"
         << std::right << std::setw(8) << "p fold"
         << '\n';

      for (auto const size : sizes)
      {
         std::vector<int> v(size);
         std::iota(std::begin(v), std::end(v), 1);

         auto v1 = v;
         auto s1 = 0LL;

         auto tsm = perf_timer<>::duration([&] {
            std::transform(std::begin(v1), std::end(v1), std::begin(v1), [](int const i) {return i + i; }); });
         auto tsf = perf_timer<>::duration([&] {
            s1 = std::accumulate(std::begin(v1), std::end(v1), 0LL, std::plus<>()); });

         auto v2 = v;
         auto s2 = 0LL;
         auto tpm = perf_timer<>::duration([&] {
            parallel_map(std::begin(v2), std::end(v2), [](int const i) {return i + i; }); });
         auto tpf = perf_timer<>::duration([&] {
            s2 = parallel_reduce(std::begin(v2), std::end(v2), 0LL, std::plus<>()); });

         assert(v1 == v2);
         assert(s1 == s2);

         std::cout
            << std::right << std::setw(8) << std::setfill(' ') << size
            << std::right << std::setw(8) << std::chrono::duration<double, std::micro>(tsm).count()
            << std::right << std::setw(8) << std::chrono::duration<double, std::micro>(tpm).count()
            << std::right << std::setw(8) << std::chrono::duration<double, std::micro>(tsf).count()
            << std::right << std::setw(8) << std::chrono::duration<double, std::micro>(tpf).count()
            << '\n';
      }
   }

   void execute()
   {
      test_mapreduce_threads();
   }
}