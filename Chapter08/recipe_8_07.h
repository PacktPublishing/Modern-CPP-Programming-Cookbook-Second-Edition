#pragma once

#include <iostream>
#include <thread>
#include <mutex>
#include <future>

namespace recipe_8_07
{
   std::mutex g_mutex;

   void do_something()
   {
      // simulate long running operation
      {
         using namespace std::chrono_literals;
         std::this_thread::sleep_for(2s);
      }

      std::lock_guard<std::mutex> lock(g_mutex);
      std::cout << "operation 1 done" << '\n';
   }

   void do_something_else()
   {
      // simulate long running operation
      {
         using namespace std::chrono_literals;
         std::this_thread::sleep_for(1s);
      }

      std::lock_guard<std::mutex> lock(g_mutex);
      std::cout << "operation 2 done" << '\n';
   }

   int compute_something()
   {
      // simulate long running operation
      {
         using namespace std::chrono_literals;
         std::this_thread::sleep_for(2s);
      }

      return 42;
   }

   int compute_something_else()
   {
      // simulate long running operation
      {
         using namespace std::chrono_literals;
         std::this_thread::sleep_for(1s);
      }

      return 24;
   }

   void execute()
   {
      {
         auto f = std::async(std::launch::async, do_something);

         do_something_else();

         f.wait();

         std::cout << "all done!" << '\n';
      }

      {
         auto f = std::async(std::launch::async, compute_something);

         auto value = compute_something_else();

         value += f.get();

         std::cout << value << '\n';
      }

      {
         auto f = std::async(std::launch::async, do_something);

         while (true)
         {
            using namespace std::chrono_literals;
            auto status = f.wait_for(500ms);
            if (status == std::future_status::ready)
               break;

            std::cout << "waiting..." << '\n';
         }

         std::cout << "done!" << '\n';
      }
   }
}