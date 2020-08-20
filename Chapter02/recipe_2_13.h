#pragma once

#ifdef HAS_FORMAT_LIBRARY
#include <format>
#include <chrono>
#include <ctime>
#include <string>
#include <vector>
#include <iterator>
#include <string>
#endif

namespace recipe_2_13
{
   void execute()
   {
#ifdef HAS_FORMAT_LIBRARY
      {
         auto text = std::format("{} is {}", "John", 42);
      }

      {
         auto text = std::format("{0} is {1}", "John", 42);
      }

      {
         auto text = std::format("{0} hex is {0:08X}", 42);

         auto now = std::chrono::system_clock::now();
         auto time = std::chrono::system_clock::to_time_t(now);
         auto text = std::format("Today is {:%Y-%m-%d}", *std::localtime(&time));
      }

      {
         std::vector<char> buf;
         std::format_to(std::back_inserter(buf), "{} is {}", "John", 42);
      }

      {
         auto size = std::formatted_size("{} is {}", "John", 42);
         std::vector<char> buf(size);
         std::format_to(buf.data(), "{} is {}", "John", 42);
      }

      {
         char buf[100];
         auto result = std::format_to_n(buf, sizeof(buf), "{} is {}", "John", 42);
      }

      {
         auto t1 = std::format("{:5}", 42);    // "   42"
         auto t2 = std::format("{:5}", 'x');   // "x    "
         auto t3 = std::format("{:*<5}", 'x'); // "x****"
         auto t4 = std::format("{:*>5}", 'x'); // "****x"
         auto t5 = std::format("{:*^5}", 'x'); // "**x**"
         auto t6 = std::format("{:5}", true);  // "true "
      }

      {
         auto t7 = std::format("{0:},{0:+},{0:-},{0: }", 42);   // "42,+42,42, 42"
         auto t8 = std::format("{0:},{0:+},{0:-},{0: }", -42);  // "-42,-42,-42,-42"
      }

      {
         auto t9  = std::format("{:+05d}", 42); // "+0042"
         auto t10 = std::format("{:#05x}", 42); // "0x02a"
         auto t11 = std::format("{:<05}", -42); // "-42  "
      }
#endif 
   }
}