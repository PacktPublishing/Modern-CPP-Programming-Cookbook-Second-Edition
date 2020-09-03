#pragma once

#include <thread>
#include <mutex>
#include <condition_variable>
#include <iostream>
#include <queue>
#include <random>
#include <array>
#include <vector>

namespace recipe_8_05
{
   using namespace std::chrono_literals;

   std::mutex              g_lockprint;
   std::mutex              g_lockqueue;
   std::condition_variable g_queuecheck;
   std::queue<int>         g_buffer;
   bool                    g_done;

   void producer(
      int const id,
      std::mt19937& generator,
      std::uniform_int_distribution<int>& dsleep,
      std::uniform_int_distribution<int>& dcode)
   {
      for (int i = 0; i < 5; ++i)
      {
         // simulate work
         std::this_thread::sleep_for(std::chrono::seconds(dsleep(generator)));

         // generate data
         int value = id * 100 + dcode(generator);

         {
            std::unique_lock<std::mutex> locker(g_lockprint);
            std::cout << "[produced]: " << value << '\n';
         }

         // notify consumers
         {
            std::unique_lock<std::mutex> locker(g_lockqueue);
            g_buffer.push(value);
            g_queuecheck.notify_one();
         }
      }
   }

   void consumer()
   {
      // loop until end is signaled
      while (!g_done)
      {
         std::unique_lock<std::mutex> locker(g_lockqueue);

         g_queuecheck.wait_for(
            locker, 
            std::chrono::seconds(1),
            [&]() {return !g_buffer.empty(); });

         // if there are values in the queue process them
         while (!g_done && !g_buffer.empty())
         {
            std::unique_lock<std::mutex> locker(g_lockprint);
            std::cout
               << "[consumed]: " << g_buffer.front()
               << '\n';
            g_buffer.pop();
         }
      }
   }

   void simple_example()
   {
      std::condition_variable cv;
      std::mutex              cv_mutex; // data mutex
      std::mutex              io_mutex; // I/O mutex
      int                     data = 0;

      std::cout << "simple example start\n";

      std::thread p([&]() {
         // simulate long running operation
         {
            using namespace std::chrono_literals;
            std::this_thread::sleep_for(2s);
         }
         // produce
         {
            std::unique_lock lock(cv_mutex);
            data = 42;
         }
         // print message
         {
            std::lock_guard l(io_mutex);
            std::cout << "produced " << data << '\n';
         }

         cv.notify_one();
      });

      std::thread c([&]() {
         // wait for notification
         {
            std::unique_lock lock(cv_mutex);
            cv.wait(lock);
         }

         {
            std::lock_guard lock(io_mutex);
            std::cout << "consumed " << data << '\n';
         }
      });

      p.join();
      c.join();

      std::cout << "simple example end\n";
   }

   void complex_example()
   {
      auto seed_data = std::array<int, std::mt19937::state_size> {};
      std::random_device rd{};

      std::generate(std::begin(seed_data), std::end(seed_data), std::ref(rd));
      std::seed_seq seq(std::begin(seed_data), std::end(seed_data));
      auto generator = std::mt19937{ seq };
      auto dsleep = std::uniform_int_distribution<>{ 1, 5 };
      auto dcode = std::uniform_int_distribution<>{ 1, 99 };

      std::cout << "start producing and consuming..." << '\n';

      std::thread consumerthread(consumer);

      std::vector<std::thread> threads;
      for (int i = 0; i < 5; ++i)
      {
         threads.emplace_back(
            producer,
            i + 1,
            std::ref(generator),
            std::ref(dsleep),
            std::ref(dcode));
      }

      // work for the workers to finish
      for (auto& t : threads)
         t.join();

      // notify the logger to finish and wait for it
      g_done = true;
      consumerthread.join();

      std::cout << "done producing and consuming" << '\n';
   }

   void execute()
   {
      simple_example();
      complex_example();
   }
}