#pragma once

#include <chrono>
#include <string>
#include <iostream>
#include <cassert>

namespace recipe_6_01
{
   void execute()
   {
      {
         std::chrono::hours         half_day(12);
         std::chrono::minutes       half_hour(30);
         std::chrono::seconds       half_minute(30);
         std::chrono::milliseconds  half_second(500);
         std::chrono::microseconds  half_milisecond(500);
         std::chrono::nanoseconds   half_microsecond(500);
      }

      {
         using namespace std::chrono_literals;

         auto half_day        = 12h;
         auto half_hour       = 30min;
         auto half_minute     = 30s;
         auto half_second     = 500ms;
         auto half_milisecond = 500us;
         auto half_microsecond= 500ns;
      }

      {
         std::chrono::hours   half_day_in_h(12);
         std::chrono::minutes half_day_in_min(half_day_in_h);

         std::cout << half_day_in_h.count() << "h" << '\n';
         std::cout << half_day_in_min.count() << "min" << '\n';
      }

      {
         using namespace std::chrono_literals;

         auto total_seconds = 12345s;
         auto hours = std::chrono::duration_cast<std::chrono::hours>(total_seconds);
         auto minutes = std::chrono::duration_cast<std::chrono::minutes>(total_seconds % 1h);
         auto seconds = std::chrono::duration_cast<std::chrono::seconds>(total_seconds % 1min);

         std::cout << hours.count() << ':' 
                   << minutes.count() << ':' 
                   << seconds.count() << '\n'; // 3:25:45
      }

      {
         using namespace std::chrono_literals;

         auto total_seconds = 12345s;
         auto m1 = std::chrono::floor<std::chrono::minutes>(total_seconds); // 205 min
         auto m2 = std::chrono::round<std::chrono::minutes>(total_seconds); // 206 min
         auto m3 = std::chrono::ceil<std::chrono::minutes>(total_seconds);  // 206 min
         auto sa = std::chrono::abs(total_seconds);
      }

      {
         using namespace std::chrono_literals;

         auto d1 = 1h + 23min + 45s; // d1 = 5025s
         auto d2 = 3h + 12min + 50s; // d2 = 11570s
         if (d1 < d2) {}
      }

      {
         using namespace std::chrono_literals;

         std::chrono::duration<double, std::ratio<10>> d(1.2); // 12 sec

         assert(std::chrono::duration_cast<std::chrono::seconds>(d).count() == (12s).count());
      }
   }
}