#pragma once

#include <string>
#include <iostream>
#include <iomanip>

namespace recipe_7_06
{
   void write_time()
   {
      auto now = std::chrono::system_clock::now();
      auto stime = std::chrono::system_clock::to_time_t(now);
      auto ltime = std::localtime(&stime);

#ifdef _WIN32
      auto loc_uk = std::locale{ "English_UK.1252" };
#else
      auto loc_uk = std::locale{ "en_GB.utf8" };
#endif

      std::cout.imbue(loc_uk);

      std::cout << std::put_time(ltime, "%c") << '\n';        // Sun 04 Dec 2016 05:26:47 JST
      std::cout << std::put_time(ltime, "%Y-%m-%d") << '\n';  // 2016-12-04
      std::cout << std::put_time(ltime, "%F") << '\n';        // 2016-12-04
      std::cout << std::put_time(ltime, "%T") << '\n';        // 05:26:47
      std::cout << std::put_time(ltime, "%F %T") << '\n';     // 2016-12-04 05:26:47
      std::cout << std::put_time(ltime, "%FT%T%z") << '\n';   // 2016-12-04T05:26:47+0900
      std::cout << std::put_time(ltime, "%V") << '\n';        // 48
      std::cout << std::put_time(ltime, "%Y-W%V") << '\n';    // 2016-W48
      std::cout << std::put_time(ltime, "%Y-W%V-%u") << '\n'; // 2016-W48-7
      std::cout << std::put_time(ltime, "%Y-%j") << '\n';     // 2016-339

      std::cout.imbue(std::locale::classic());
   }


   void read_time()
   {
      {
         std::istringstream stext("2016-12-04T05:26:47+0900");

         auto time = std::tm{};

         stext >> std::get_time(&time, "%Y-%m-%dT%H:%M:%S");
         if (stext.fail())
         {
            std::cout << "Parsing failed" << '\n';
         }
         else
         {
            std::cout << std::put_time(&time, "%c") << '\n';
         }
      }

      {
         std::istringstream stext("Sun 04 Dec 2016 05:35:30 JST");
#ifdef _WIN32
         auto loc_uk = std::locale{ "English_UK.1252" };
#else
         auto loc_uk = std::locale{ "en_GB.utf8" };
#endif
         stext.imbue(loc_uk);

         auto time = std::tm{};

         stext >> std::get_time(&time, "%c");
         if (stext.fail())
         {
            std::cout << "Parsing failed" << '\n';
         }
         else
         {
            std::cout << std::put_time(&time, "%c") << '\n';
         }
      }
   }

   void execute()
   {
      write_time();

      read_time();
   }
}