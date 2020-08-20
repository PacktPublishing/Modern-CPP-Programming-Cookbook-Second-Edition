#pragma once

#include <regex>
#include <string>

namespace recipe_2_11
{
   using namespace std::string_literals;

   void execute()
   {
      {
         auto text{ "abc aa bca ca bbbb"s };
         auto rx = std::regex{ R"(\b[a|b|c]{3}\b)"s };
         auto newtext = std::regex_replace(text, rx, "---"s);

         std::cout << newtext << '\n';
      }

      {
         auto text{ "abc aa bca ca bbbb"s };
         auto rx = std::regex{ R"(\b[a|b|c]{3}\b)"s };
         auto newtext = std::regex_replace(text, rx, "---"s, std::regex_constants::format_first_only);

         std::cout << newtext << '\n';
      }

      {
         auto text{ "bancila, marius"s };
         auto rx = std::regex{ R"((\w+),\s*(\w+))"s };
         auto newtext = std::regex_replace(text, rx, "$2 $1"s);

         std::cout << newtext << '\n';
      }

      {
         auto text{ "this is a example with a error"s };
         auto rx = std::regex{ R"(\ba ((a|e|i|u|o)\w+))"s };
         auto newtext = std::regex_replace(text, rx, "an $1");

         std::cout << newtext << '\n';
      }

      {
         auto text{ "today is 1.06.2016!!"s };
         auto rx = std::regex{ R"((\d{1,2})(\.|-|/)(\d{1,2})(\.|-|/)(\d{4}))"s };
         auto newtext1 = std::regex_replace(text, rx, R"($5$4$3$2$1)");
         auto newtext2 = std::regex_replace(text, rx, R"([$`][$&][$'])");

         std::cout << newtext1 << '\n';
         std::cout << newtext2 << '\n';
      }
   }
}