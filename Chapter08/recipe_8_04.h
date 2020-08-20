
#pragma once

#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <vector>

namespace recipe_8_04
{
   std::mutex g_mutex;

   void thread_func_1()
   {
      using namespace std::chrono_literals;

      std::lock_guard<std::mutex> lock(g_mutex);
      std::cout << "running thread " << std::this_thread::get_id() << '\n';
      std::this_thread::sleep_for(2s);
      std::cout << "done in thread " << std::this_thread::get_id() << '\n';
   }

   void thread_func_2()
   {
      using namespace std::chrono_literals;

      {
         std::lock_guard<std::mutex> lock(g_mutex);
         std::cout << "running thread " << std::this_thread::get_id() << '\n';
      }

      std::this_thread::yield();
      std::this_thread::sleep_for(2s);

      {
         std::lock_guard<std::mutex> lock(g_mutex);
         std::cout << "done in thread " << std::this_thread::get_id() << '\n';
      }
   }

   void thread_func_3()
   {
      using namespace std::chrono_literals;

      g_mutex.lock();
      std::cout << "running thread " << std::this_thread::get_id() << '\n';
      std::this_thread::sleep_for(2s);
      std::cout << "done in thread " << std::this_thread::get_id() << '\n';
      g_mutex.unlock();
   }

   template <class M>
   class lock_guard
   {
   public:
      typedef M mutex_type;

      explicit lock_guard(M& Mtx) : mtx(Mtx)
      {
         mtx.lock();
      }

      lock_guard(M& Mtx, std::adopt_lock_t) : mtx(Mtx)
      {
      }

      ~lock_guard() noexcept
      {
         mtx.unlock();
      }

      lock_guard(const lock_guard&) = delete;
      lock_guard& operator=(const lock_guard&) = delete;
   private:
      M& mtx;
   };

   template <typename T>
   struct container
   {
      std::mutex mutex;
      std::vector<T> data;
   };

   template <typename T>
   void move_between(container<T>& c1, container<T>& c2,
      T const value)
   {
      std::lock(c1.mutex, c2.mutex);

      std::lock_guard<std::mutex> l1(c1.mutex, std::adopt_lock);
      std::lock_guard<std::mutex> l2(c2.mutex, std::adopt_lock);

      c1.data.erase(
         std::remove(c1.data.begin(), c1.data.end(), value),
         c1.data.end());
      c2.data.push_back(value);
   }

   template <typename T>
   void print_container(container<T> const& c)
   {
      for (auto const& e : c.data) std::cout << e << ' ';
      std::cout << '\n';
   }

   void execute()
   {
      {
         std::vector<std::thread> threads;
         for (int i = 0; i < 5; ++i)
            threads.emplace_back(thread_func_1);

         for (auto& t : threads)
            t.join();
      }

      {
         std::vector<std::thread> threads;
         for (int i = 0; i < 5; ++i)
            threads.emplace_back(thread_func_2);

         for (auto& t : threads)
            t.join();
      }

      {
         container<int> c1;
         c1.data.push_back(1);
         c1.data.push_back(2);
         c1.data.push_back(3);

         container<int> c2;
         c2.data.push_back(4);
         c2.data.push_back(5);
         c2.data.push_back(6);

         print_container(c1);
         print_container(c2);

         std::thread t1(move_between<int>, std::ref(c1), std::ref(c2), 3);
         std::thread t2(move_between<int>, std::ref(c2), std::ref(c1), 6);

         t1.join();
         t2.join();

         print_container(c1);
         print_container(c2);

      }
   }
}