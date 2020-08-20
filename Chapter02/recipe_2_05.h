#pragma once

#include <string>

namespace recipe_2_05
{
   void execute()
   {
      using namespace std::string_literals;

      {
         auto filename{ "C:\\Users\\Marius\\Documents\\"s };

         auto pattern{ "(\\w+)=(\\d+)$"s };

         auto sqlselect{
            "SELECT *\n\
FROM Books\n\
WHERE Publisher=\'Paktpub\'\n\
ORDER BY PubDate DESC"s };
      }

      {
         auto filename{ R"(C:\Users\Marius\Documents\)"s };

         auto pattern{ R"((\w+)=(\d+)$)"s };

         auto sqlselect{
            R"(SELECT *
FROM Books
WHERE Publisher='Paktpub'
ORDER BY PubDate DESC)"s };
      }

      {
         auto filename1{ R"(C:\Users\Marius\Documents\)"s };
         auto filename2{ R"(C:\\Users\\Marius\\Documents\\)"s };

         // prints C:\Users\Marius\Documents\ 
         std::cout << filename1 << '\n';

         // prints C:\\Users\\Marius\\Documents\\ 
         std::cout << filename2 << '\n';

         auto text{ R"!!(This text contains both "( and )".)!!"s };
         std::cout << text << '\n';
      }

      {
         auto t1{ LR"(text)" };	// const wchar_t*
         auto t2{ u8R"(text)" };	// const char*
         auto t3{ uR"(text)" };	// const char16_t*
         auto t4{ UR"(text)" };	// const char32_t*

         auto t5{ LR"(text)"s }; // wstring
         auto t6{ u8R"(text)"s };// string
         auto t7{ uR"(text)"s }; // u16string
         auto t8{ UR"(text)"s }; // u32string
      }
   }
}
