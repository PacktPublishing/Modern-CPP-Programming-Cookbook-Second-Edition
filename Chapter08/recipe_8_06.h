#pragma once

#include <iostream>
#include <thread>
#include <future>
#include <mutex>

namespace recipe_8_06
{
   std::mutex g_mutex;

   void produce_value(std::promise<int>& p)
   {
      // simulate long running operation
      {
         using namespace std::chrono_literals;
         std::this_thread::sleep_for(2s);
      }

      p.set_value(42);
   }

   void consume_value(std::future<int>& f)
   {
      auto value = f.get();

      std::lock_guard<std::mutex> lock(g_mutex);
      std::cout << value << '\n';
   }

   void execute()
   {
      std::promise<int> p;
      std::thread t1(produce_value, std::ref(p));

      std::future<int> f = p.get_future();
      std::thread t2(consume_value, std::ref(f));

      t1.join();
      t2.join();
   }
}