#pragma once

#include <bitset>
#include <string>
#include <iostream>

namespace recipe_5_02
{
   using namespace std::string_literals;

#define BORDER_NONE     0x00
#define BORDER_LEFT     0x01
#define BORDER_TOP      0x02
#define BORDER_RIGHT    0x04
#define BORDER_BOTTOM   0x08

   struct border_flags
   {
      static const int left = 0;
      static const int top = 1;
      static const int right = 2;
      static const int bottom = 3;
   };

   void apply_style(unsigned int const style)
   {
      if (style & BORDER_BOTTOM) {}
   }

   template <size_t N>
   std::vector<unsigned long> bitset_to_vectorulong(std::bitset<N> bs)
   {
      auto result = std::vector<unsigned long> {};
      auto const size = 8 * sizeof(unsigned long);
      auto const mask = std::bitset<N>{ static_cast<unsigned long>(-1) };

      auto totalbits = 0;
      while (totalbits < N)
      {
         auto value = (bs & mask).to_ulong();
         result.push_back(value);
         bs >>= size;
         totalbits += size;
      }

      return result;
   }

   void execute()
   {
      // construct
      {
         std::bitset<8> b1;            // [0,0,0,0,0,0,0,0]

         std::bitset<8> b2{ 10 };      // [0,0,0,0,1,0,1,0]

         std::bitset<8> b3{ "1010"s }; // [0,0,0,0,1,0,1,0]

         std::bitset<8> b4{ "ooooxoxo"s, 0, std::string::npos, 'o', 'x' };
         // [0,0,0,0,1,0,1,0]
      }

      // element access
      {
         std::bitset<8> bs{ 10 };
         std::cout << "has " << bs.count() << " 1s" << '\n';

         if (bs.any()) std::cout << "has some 1s" << '\n';
         if (bs.all()) std::cout << "has only 1s" << '\n';
         if (bs.none()) std::cout << "has no 1s" << '\n';

         if (!bs.test(0)) std::cout << "even" << '\n';
         if(!bs[0]) std::cout << "even" << '\n';
      }

      // modifiers
      {
         std::bitset<8> b1{ 42 }; // [0,0,1,0,1,0,1,0]
         std::bitset<8> b2{ 11 }; // [0,0,0,0,1,0,1,1]

         auto b3 = b1 | b2;       // [0,0,1,0,1,0,1,1]
         auto b4 = b1 & b2;       // [0,0,0,0,1,0,1,0]
         auto b5 = b1 ^ b2;       // [1,1,0,1,1,1,1,0]
         auto b6 = ~b1;           // [1,1,0,1,0,1,0,1]

         auto b7 = b1 << 2;       // [1,0,1,0,1,0,0,0]
         auto b8 = b1 >> 2;       // [0,0,0,0,1,0,1,0]

         b1.flip();               // [1,1,0,1,0,1,0,1]
         b1.flip(0);              // [1,1,0,1,0,1,0,0]
         b1.set(0, true);         // [1,1,0,1,0,1,0,1]
         b1.set(0, false);        // [1,1,0,1,0,1,0,0]
         b1.reset(2);             // [1,1,0,1,0,0,0,0]
      }

      // conversion
      {
         std::bitset<8> bs{ 42 };

         auto n1 = bs.to_ulong();   // n1 = 42UL
         auto n2 = bs.to_ullong();  // n2 = 42ULL

         auto s1 = bs.to_string();           // s1 = "00101010"
         auto s2 = bs.to_string('o', 'x');   // s2 = "ooxoxoxo"
      }

      // C-like style
      {
         // initialize with no flags
         unsigned int style = BORDER_NONE;
         // set a flag
         style = BORDER_BOTTOM;
         // add more flags
         style |= BORDER_LEFT | BORDER_RIGHT | BORDER_TOP;
         // remove some flags
         style &= ~BORDER_LEFT;
         style &= ~BORDER_RIGHT;
         // test if a flag is set
         if ((style & BORDER_BOTTOM) == BORDER_BOTTOM) {}
         // pass the flags as argument to a function
         apply_style(style);
      }

      // C++ style
      {
         // initialize with no flags
         std::bitset<4> style;
         // set a flag
         style.set(border_flags::bottom);
         // set more flags
         style
            .set(border_flags::left)
            .set(border_flags::top)
            .set(border_flags::right);
         // remove some flags
         style[border_flags::left] = 0;
         style.reset(border_flags::right);
         // test if a flag is set
         if (style.test(border_flags::bottom)) {}
         // pass the flags as argument to a function
         apply_style(style.to_ulong());
      }

      {
         std::bitset<128> bs =
            (std::bitset<128>(0xFEDC) << 96) |
            (std::bitset<128>(0xBA98) << 64) |
            (std::bitset<128>(0x7654) << 32) |
            std::bitset<128>(0x3210);

         std::cout << bs << '\n';

         auto result = bitset_to_vectorulong(bs);
         for (auto const v : result) 
            std::cout << std::hex << v << '\n';

         std::cout << std::dec;
      }
   }
}