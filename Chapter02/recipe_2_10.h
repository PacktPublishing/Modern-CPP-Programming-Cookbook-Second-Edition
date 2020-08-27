#pragma once

#include <regex>
#include <string>

namespace recipe_2_10
{
   using namespace std::string_literals;

   void execute()
   {
      auto text{
         R"(
#remove # to uncomment a line
timeout=120
server = 127.0.0.1

#retrycount=3
)"s
      };

      auto rx = std::regex{ R"(^(?!#)(\w+)\s*=\s*([\w\d]+[\w\d._,\-:]*)$)"s };

      {
         auto match = std::smatch{};
         if (std::regex_search(text, match, rx))
         {
            std::cout << match[1] << '=' << match[2] << '\n';
         }
      }

      {
         auto end = std::sregex_iterator{};
         for (auto it = std::sregex_iterator{ std::begin(text), std::end(text), rx };
            it != end;
            ++it)
         {
            std::cout << '\'' << (*it)[1] << "\'=\'" << (*it)[2] << '\''
               << '\n';
         }
      }

      {
         auto end = std::sregex_token_iterator{};
         for (auto it = std::sregex_token_iterator{ std::begin(text), std::end(text), rx };
            it != end;
            ++it)
         {
            std::cout << *it << '\n';
         }
      }

      {
         auto end = std::sregex_token_iterator{};
         for (auto it = std::sregex_token_iterator{ std::begin(text), std::end(text), rx, 1 };
            it != end;
            ++it)
         {
            std::cout << *it << '\n';
         }
      }

      {
         auto end = std::sregex_token_iterator{};
         for (auto it = std::sregex_token_iterator{ std::begin(text), std::end(text), rx, -1 };
            it != end;
            ++it)
         {
            std::cout << *it << '\n';
         }
      }
   }
}