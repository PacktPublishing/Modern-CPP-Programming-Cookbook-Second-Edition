#pragma once

#include <string>
#include <iostream>
#include <iomanip>

namespace recipe_7_04
{
   using namespace std::string_literals;

   struct Company
   {
      std::string Name;
      std::string Industry;
      double      Revenue;
      bool        RevenueIncrease;
      double      Growth;
      int         Employees;
      std::string Country;
   };


   void print1()
   {
      // https://en.wikipedia.org/wiki/List_of_largest_companies_by_revenue
      std::vector<Company> companies
      {
         { "Walmart"s, "Retail"s, 482, false, 0.71, 2300000, "US"s },
         { "State Grid"s, "Electric utility"s, 330, false, 2.91, 927839, "China"s },
         { "Saudi Aramco"s, "Oil and gas"s, 311, true, 40.11, 65266, "Saudi Arabia"s },
         { "China National Petroleum"s, "Oil and gas"s, 299, false, 30.21, 1589508, "China"s },
         { "Sinopec Group"s, "Oil and gas"s, 294, false, 34.11, 810538, "China"s },
      };

      for (auto const & company : companies)
      {
         std::cout << std::left << std::setw(26) << std::setfill(' ') << company.Name;
         std::cout << std::left << std::setw(18) << std::setfill(' ') << company.Industry;
         std::cout << std::left << std::setw(5) << std::setfill(' ') << company.Revenue;
         std::cout << std::left << std::setw(5) << std::setfill(' ')
            << std::boolalpha << company.RevenueIncrease;
         std::cout << std::right << std::setw(5) << std::setfill(' ')
            << std::fixed << std::setprecision(1) << company.Growth
            << std::defaultfloat << std::setprecision(6) << ' ';
         std::cout << std::right << std::setw(8) << std::setfill(' ') << company.Employees << ' ';
         std::cout << std::left << std::setw(2) << std::setfill(' ') << company.Country;
         std::cout << '\n';
      }
   }

   std::string to_roman(unsigned int value)
   {
      struct roman_t { unsigned int value; char const* numeral; };
      const static roman_t rarr[13] =
      {
         { 1000, "M" },{ 900, "CM" },
         { 500, "D" },{ 400, "CD" },
         { 100, "C" },{ 90, "XC" },
         { 50, "L" },{ 40, "XL" },
         { 10, "X" },{ 9, "IX" },
         { 5, "V" },{ 4, "IV" },
         { 1, "I" }
      };

      std::string result;
      for (auto const & number : rarr)
      {
         while (value >= number.value)
         {
            result += number.numeral;
            value -= number.value;
         }
      }

      return result;
   }

   struct Chapter
   {
      int         Number;
      std::string Title;
      int         Page;
   };

   struct BookPart
   {
      std::string          Title;
      std::vector<Chapter> Chapters;
   };

   struct Book
   {
      std::string             Title;
      std::vector<BookPart>   Parts;
   };

   void print_toc(Book const & book)
   {
      std::cout << book.Title << '\n';
      for (auto const & part : book.Parts)
      {
         std::cout << std::left << std::setw(15) << std::setfill(' ') << part.Title << '\n';
         std::cout << std::left << std::setw(15) << std::setfill('-') << '-' << '\n';

         for (auto const & chapter : part.Chapters)
         {
            std::cout << std::right << std::setw(4) << std::setfill(' ') << to_roman(chapter.Number) << ' ';
            std::cout << std::left << std::setw(35) << std::setfill('.') << chapter.Title;
            std::cout << std::right << std::setw(3) << std::setfill('.') << chapter.Page << '\n';
         }
      }
   }

   void print2()
   {
      auto book = Book
      {
         "THE FELLOWSHIP OF THE RING"s,
         {
            {
               "BOOK ONE"s,
               {
                  { 1, "A Long-expected Party"s, 21 },
                  { 2, "The Shadow of the Past"s, 42 },
                  { 3, "Three Is Company"s, 65 },
                  { 4, "A Short Cut to Mushrooms"s, 86 },
                  { 5, "A Conspiracy Unmasked"s, 98 },
                  { 6, "The Old Forest"s,  109 },
                  { 7, "In the House of Tom Bombadil"s, 123 },
                  { 8, "Fog on the Barrow-downs"s, 135 },
                  { 9, "At the Sign of The Prancing Pony"s, 149 },
                  { 10, "Strider"s, 163 },
                  { 11, "A Knife in the Dark"s, 176 },
                  { 12, "Flight to the Ford"s, 197 },
               },
            },
            {
               "BOOK TWO"s,
               {
                  { 1, "Many Meetings"s, 219 },
                  { 2, "The Council of Elrond"s, 239 },
                  { 3, "The Ring Goes South"s, 272 },
                  { 4, "A Journey in the Dark"s, 295 },
                  { 5, "The Bridge of Khazad-dum"s, 321 },
                  { 6, "Lothlorien"s, 333 },
                  { 7, "The Mirror of Galadriel"s, 353 },
                  { 8, "Farewell to Lorien"s, 367 },
                  { 9, "The Great River"s, 380 },
                  { 10, "The Breaking of the Fellowship"s, 390 },
               },
            },
         }
      };

      print_toc(book);
   }

   void execute()
   {
      print1();

      print2();

      {
         std::cout << std::boolalpha << true << '\n';    // true
         std::cout << false << '\n';                     // false
         std::cout << std::noboolalpha << false << '\n'; // 0
      }

      {
         std::cout << std::right << std::setw(10) << "right" << '\n';
         std::cout << std::setw(10) << "text" << '\n';
         std::cout << std::left << std::setw(10) << "left" << '\n';
      }

      {
         std::cout << std::fixed << 0.25 << '\n';        // 0.250000
         std::cout << std::scientific << 0.25 << '\n';   // 2.500000e-01
         std::cout << std::hexfloat << 0.25 << '\n';     // 0x1p-2
         std::cout << std::defaultfloat << 0.25 << '\n'; // 0.25
      }

      {
         std::cout << std::oct << 42 << '\n'; // 52
         std::cout << std::hex << 42 << '\n'; // 2a
         std::cout << std::dec << 42 << '\n'; // 42
      }

      {
         std::cout << std::right
            << std::setfill('.') << std::setw(10)
            << "right" << '\n';  // .....right
      }

      {
         std::cout << std::fixed << std::setprecision(2)
            << 12.345 << '\n';  // 12.35
      }
   }
}