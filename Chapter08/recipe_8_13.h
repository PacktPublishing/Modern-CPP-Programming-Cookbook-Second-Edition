#pragma once

#ifdef HAS_LATCHES_BARRIERS
#include <vector>
#include <thread>
#include <iostream>
#include <functional>

#include <latch>
#include <barrier>
#include <semaphore>
#include <stop_token>
#endif

namespace recipe_8_13
{
   void process(std::vector<int> const& data)   
   {
      for (auto const e : data)
      {
         std::cout << e << ' ';
      }
      
      std::cout << '\n';
   }

   int create(int const i, int const factor)
   {
      return i * factor;
   }

#ifdef HAS_LATCHES_BARRIERS
   void test_latches()
   {
      int const jobs = 4;
      std::latch work_done(jobs);
      std::vector<int> data(jobs);
      std::vector<std::jthread> threads;
      for (int i = 1; i <= jobs; ++i)
      {
         threads.push_back(std::jthread([&data, i, &work_done] {
            using namespace std::chrono_literals;
            std::this_thread::sleep_for(1s); // simulate work

            data[i] = create(i, 2); // create data

            work_done.count_down(); // decrement counter
            }));

      }
      work_done.wait();             // wait for all jobs to finish
      process(data);                // process data from all jobs
   }

   void test_barriers()
   {
      int const jobs = 4;
      std::vector<int> data(jobs);
      int cycle = 1;
      std::stop_source st;

      std::barrier<std::function<void()>>
         work_done(
            jobs,                      // counter
            [&data, &cycle, &st]() {   // completion function
               process(data);          // process data from all jobs
               cycle++;
               if (cycle == 10)        // stop after ten cycles
                  st.request_stop();
            });

      std::vector<std::jthread> threads;
      for (int i = 1; i <= jobs; ++i)
      {
         threads.push_back(std::jthread(
            [&cycle, &work_done](std::stop_token st, int const i)
            {
               while (!st.stop_requested())
               {
                  using namespace std::chrono_literals;
                  std::this_thread::sleep_for(200ms); // simulate work

                  data[i] = create(i, cycle);   // create data 

                  work_done.arrive_and_wait();  // decrement counter
               }
            }));
      }

      for (auto& t : threads) t.join();
   }

   void test_semaphores()
   {
      int const jobs = 4;
      std::vector<int> data;

      std::binary_semaphore bs;

      for (int i = 1; i <= jobs; ++i)
      {
         threads.push_back(std::jthread([&data, i, &bs] {
            for (int k = 1; k < 5; ++k)
            {
               using namespace std::chrono_literals;
               std::this_thread::sleep_for(200ms);   // simulate work
               int value = create(i, k);     // create data

               bs.acquire();                 // acquire the semaphore
               data.push_back(value);        // write to the shared resource
               bs.release();                 // release the semaphore
            }
         }));
      }

      process(data);                         // process data from all jobs
   }
#endif

   void execute()
   {
#ifdef HAS_LATCHES_BARRIERS
      test_latches();
      test_barriers();
      test_semaphores();
#endif
   }
}
