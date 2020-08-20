#pragma once

#include <iostream>
#include <string>
#include <sstream>

namespace recipe_2_01
{
   void execute()
   {
      auto si = std::to_string(42);       // si="42"
      auto sl = std::to_string(42l);      // sl="42"
      auto su = std::to_string(42u);      // su="42"
      auto sd = std::to_string(42.0);     // sd="42.000000"
      auto sld = std::to_string(42.0l);   // sld="42.000000"

      auto i1 = std::stoi("42");
      auto i2 = std::stoi("   42");
      auto i3 = std::stoi("   42fortytwo");
      auto i4 = std::stoi("+42");
      auto i5 = std::stoi("-42");

      auto i6 = std::stoi("052", nullptr, 8);
      auto i7 = std::stoi("052", nullptr, 0);
      auto i8 = std::stoi("0x2A", nullptr, 16);
      auto i9 = std::stoi("0x2A", nullptr, 0);
      auto i10 = std::stoi("101010", nullptr, 2);
      auto i11 = std::stoi("22", nullptr, 20);
      auto i12 = std::stoi("-22", nullptr, 20);

      auto pos = size_t{ 0 };
      auto i13 = std::stoi("42", &pos);      // pos = 2
      auto i14 = std::stoi("-42", &pos);     // pos = 3
      auto i15 = std::stoi("  +42dec", &pos);// pos = 5

      try
      {
         auto i16 = std::stoi("");
      }
      catch (std::exception const & e)
      {
         // prints "invalid stoi argument"
         std::cout << e.what() << '\n';
      }

      try
      {
         auto i17 = std::stoll("12345678901234");  // OK
         auto i18 = std::stoi("12345678901234");   // throws std::out_of_range
      }
      catch (std::exception const & e)
      {
         // prints stoi argument out of range
         std::cout << e.what() << '\n';
      }

      auto d1 = std::stod("123.45");         // d1 =  123.45000000000000
      auto d2 = std::stod("+123.45");        // d2 =  123.45000000000000
      auto d3 = std::stod("-123.45");        // d3 = -123.45000000000000
      auto d4 = std::stod("  123.45");       // d4 =  123.45000000000000
      auto d5 = std::stod("  -123.45abc");   // d5 = -123.45000000000000
      auto d6 = std::stod("1.2345e+2");      // d6 =  123.45000000000000
      auto d7 = std::stod("0xF.6E6666p3");   // d7 =  123.44999980926514

      auto d8 = std::stod("INF");            // d8 = inf
      auto d9 = std::stod("-infinity");      // d9 = -inf
      auto d10 = std::stod("NAN");           // d10 = nan
      auto d11 = std::stod("-nanabc");       // d11 = -nan
   }
}