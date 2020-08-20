#pragma once

#include <iostream>
#include <thread>
#include <string>
#include <chrono>
#include <iomanip>

namespace recipe_8_01
{
   void func1()
   {
      std::cout << "thread func without params" << '\n';
   }

   void func2(int const i, double const d, std::string const s)
   {
      std::cout << i << ", " << d << ", " << s << '\n';
   }

   void func3(int & i)
   {
      i *= 2;
   }

   inline void print_time()
   {
      auto now = std::chrono::system_clock::now();
      auto stime = std::chrono::system_clock::to_time_t(now);
      auto ltime = std::localtime(&stime);

      std::cout << std::put_time(ltime, "%c") << '\n';
   }

   void func4()
   {
      using namespace std::chrono;

      print_time();

      std::this_thread::sleep_for(2s);

      print_time();
   }

   void func5()
   {
      using namespace std::chrono;

      print_time();

      std::this_thread::sleep_until(
         std::chrono::system_clock::now() + 2s);

      print_time();
   }

   void func6(std::chrono::seconds timeout)
   {
      auto now = std::chrono::system_clock::now();
      auto then = now + timeout;

      do
      {
         std::this_thread::yield();
      } while (std::chrono::system_clock::now() < then);
   }

   void execute()
   {
      {
         std::thread t(func1);
         t.join();
      }

      {
         std::thread t([]() {
            std::cout << "thread func without params" 
                      << '\n'; });
         t.join();
      }

      {
         std::thread t(func2, 42, 42.0, "42");
         t.join();
      }

      {
         std::thread t(
            [](int const i, double const d, std::string const s)
            {
               std::cout << i << ", " << d << ", " << s 
                         << '\n';
            }, 
            42, 42.0, "42");
         t.join();
      }

      {
         int n = 42;
         std::thread t(func3, std::ref(n));
         t.join();

         std::cout << n << '\n';
      }

      {
         int n = 42;
         std::thread t([](int & i) {i *= 2; }, std::ref(n));
         t.join();

         std::cout << n << '\n';
      }

      {
         std::thread t(func4);
         t.join();
      }

      {
         std::thread t(func5);
         t.join();
      }

      {
         std::thread t(func6, std::chrono::seconds(2));
         t.join();

         print_time();
      }
   }
}