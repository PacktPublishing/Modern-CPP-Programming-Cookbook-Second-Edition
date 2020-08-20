#pragma once

#include <chrono>
#include <iostream>

namespace recipe_6_02
{
#ifdef HAS_CALENDAR_AND_TIMEZONES
   inline int number_of_days(date::sys_days const& first,
      date::sys_days const& last)
   {
      return (last - first).count();
   }

#endif

   void execute()
   {
#ifdef HAS_CALENDAR_AND_TIMEZONES
      {
         // format: year / month /day
         year_month_day d1 = 2020y / 1 / 15;
         year_month_day d2 = 2020y / January / 15;
         // format: day / month / year
         year_month_day d3 = 15d / 1 / 2020;
         year_month_day d4 = 15d / January / 2020;
         // format: month / day / year
         year_month_day d5 = 1 / 15d / 2020;
         year_month_day d6 = January / 15 / 2020;
      }

      {
         // format: year / month / weekday
         year_month_weekday d1 = 2020y / January / Monday[1];
         // format: weekday / month / year
         year_month_weekday d2 = Monday[1] / January / 2020;
         // format: month / weekday / year
         year_month_weekday d3 = January / Monday[1] / 2020;
      }

      {
         auto today = floor<days>(std::chrono::system_clock::now());
         auto tomorrow = today + days{ 1 };
         auto yesterday = today - days{ 1 };
      }

      {
         year_month_day today = floor<days>(std::chrono::system_clock::now());
         year_month_day first_day_this_month = today.year() / today.month() / 1;
         year_month_day last_day_this_month = today.year() / today.month() / last;
         year_month_day last_day_feb_2020 = 2020y / February / last;

         year_month_day_last ymdl{ today.year(), month_day_last{ month{ 2 } } };
         year_month_day last_day_feb{ ymdl };
      }

      {
         auto days = number_of_days(2020_y / apr / 1, 2020_y / dec / 25);
      }

      {
         auto day = 2020_y / January / 33;
         auto is_valid = day.ok();
      }

      {
         time_of_day<std::chrono::seconds> td(13h + 12min + 11s);
         std::cout << td << '\n';  // 13:12:11
      }

      {
         auto tp = sys_days{ 2020_y / April / 1 } +12h + 30min + 45s;
         std::cout << tp << '\n';  // 2020-04-01 12:30:45
      }

      {
         auto tp = std::chrono::system_clock::now();
         auto dp = floor<days>(tp);

         time_of_day<std::chrono::milliseconds> time{ std::chrono::duration_cast<std::chrono::milliseconds>(tp - dp) };
         std::cout << time << '\n';  // 13:12:11.625

         time_of_day<std::chrono::minutes> time{ std::chrono::duration_cast<std::chrono::minutes>(tp - dp) };
         std::cout << time << '\n';  // 13:12
      }
#endif
   }
}