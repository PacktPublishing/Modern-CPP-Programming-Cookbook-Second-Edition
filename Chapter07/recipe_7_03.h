#pragma once

#include <locale>
#include <iomanip>
#include <chrono>
#include <algorithm>

namespace recipe_7_03
{
   void execute()
   {
      {
         auto loc_def = std::locale{};
#ifdef _WIN32
         auto loc_us = std::locale{ "English_US.1252" };
#else
         auto loc_us = std::locale{ "en_US.utf8" };
#endif
         auto loc1 = std::locale{ loc_def, new std::collate<wchar_t> };
         auto loc2 = std::locale{ loc_def, loc_us, std::locale::collate };
      }

      auto now = std::chrono::system_clock::now();
      auto stime = std::chrono::system_clock::to_time_t(now);
      auto ltime = std::localtime(&stime);

      std::vector<std::string> names{ "John", "adele", "Øivind", "François", "Robert", "Åke" };
      auto sort_and_print = [](std::vector<std::string> v, std::locale const & loc)
      {
         std::sort(v.begin(), v.end(), loc);
         for (auto const & s : v) std::cout << s << ' ';
         std::cout << '\n';
      };

      {
#ifdef _WIN32
         auto loc = std::locale("German_Germany.1252");
#else
         auto loc = std::locale("de_DE.utf8");
#endif
         std::cout.imbue(loc);

         std::cout << 1000.50 << '\n'; // 1.000,5
         std::cout << std::showbase << std::put_money(1050) << '\n'; // 10,50 €
         std::cout << std::put_time(ltime, "%c") << '\n'; // So 04 Dez 2016 17:54:06 JST

         sort_and_print(names, loc); // adele Åke François John Øivind Robert
      }

      {
         auto loc = std::locale("");
         std::cout.imbue(loc);

         std::cout << 1000.50 << '\n'; // 1,000.5
         std::cout << std::showbase << std::put_money(1050) << '\n'; // $10.50
         std::cout << std::put_time(ltime, "%c") << '\n'; // Sun 04 Dec 2016 05:54:06 PM JST

         sort_and_print(names, loc); // adele Åke François John Øivind Robert
      }

      {
#ifdef _WIN32
         std::locale::global(std::locale("Swedish_Sweden.1252"));
#else
         std::locale::global(std::locale("sv_SE.utf8"));
#endif

         auto loc = std::locale{};
         std::cout.imbue(loc);

         std::cout << 1000.50 << '\n'; // 1 000,5
         std::cout << std::showbase << std::put_money(1050) << '\n'; // 10,50 kr
         std::cout << std::put_time(ltime, "%c") << '\n'; // sön  4 dec 2016 18:02:29

         sort_and_print(names, loc); // adele François John Robert Åke Øivind
      }

      {
         auto loc = std::locale::classic();
         std::cout.imbue(loc);

         std::cout << 1000.50 << '\n'; // 1000.5
         std::cout << std::showbase << std::put_money(1050) << '\n'; // 1050
         std::cout << std::put_time(ltime, "%c") << '\n'; // Sun Dec  4 17:55:14 2016

         sort_and_print(names, loc); // François John Robert adele Åke Øivind
      }
   }
}