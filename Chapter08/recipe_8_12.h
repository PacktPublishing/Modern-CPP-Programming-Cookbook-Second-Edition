#pragma once

#include <iostream>
#include <thread>

namespace recipe_8_12
{
#ifdef HAS_JTHREAD
   void thread_func1(int i)
   {
      while (i-- > 0)
      {
         std::cout << i << '\n';
      }
   }

   void thread_func2(std::stop_token st, int& i)
   {
      while (!st.stop_requested() && i < 100)
      {
         using namespace std::chrono_literals;
         std::this_thread::sleep_for(200ms);
         i++;
      }
   }

   void thread_func3(std::stop_token st, int& i)
   {
      while (!st.stop_requested() && i < 100)
      {
         using namespace std::chrono_literals;
         std::this_thread::sleep_for(200ms);
         i++;
      }
   }

   void thread_func4(std::stop_token st, int& i)
   {
      while (!st.stop_requested() && i < 100)
      {
         using namespace std::chrono_literals;
         std::this_thread::sleep_for(200ms);
         i++;
      }
   }
#endif

   void execute()
   {
#ifdef HAS_JTHREAD
      // scenario 1
      {
         std::jthread t(thread_func1, 10);
      }

      // scenario 2
      {
         int a = 0;

         std::jthread t(thread_func2, std::ref(a));

         using namespace std::chrono_literals;
         std::this_thread::sleep_for(1s);

         t.request_stop();

         std::cout << a << '\n';       // prints 4

      }

      // scenario 3
      {
         int a = 0;
         int b = 10;

         std::stop_source st;

         std::jthread t1(thread_func3, st.get_token(), std::ref(a));
         std::jthread t2(thread_func3, st.get_token(), std::ref(b));

         using namespace std::chrono_literals;
         std::this_thread::sleep_for(1s);

         st.request_stop();

         std::cout << a << ' ' << b << '\n';       // prints 4 and 14
      }

      // scenario 4
      {
         int a = 0;

         std::stop_source src;
         std::stop_token token = src.get_token();
         std::stop_callback cb(token, [] {std::cout << "the end\n"; });

         std::jthread t(thread_func4, token, std::ref(a));

         using namespace std::chrono_literals;
         std::this_thread::sleep_for(1s);

         src.request_stop();

         std::cout << a << '\n';       // prints "the end" and 4
      }
#endif
   }
}