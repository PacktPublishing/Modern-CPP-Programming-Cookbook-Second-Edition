#pragma once

namespace recipe_2_07
{
   namespace binary
   {
      using byte8 = unsigned char;
      using byte16 = unsigned short;
      using byte32 = unsigned int;

      namespace binary_literals
      {
         namespace binary_literals_internals
         {
            template <typename CharT, char... bits>
            struct binary_struct;

            template <typename CharT, char... bits>
            struct binary_struct<CharT, '0', bits...>
            {
               static constexpr CharT value{
                  binary_struct<CharT, bits...>::value };
            };

            template <typename CharT, char... bits>
            struct binary_struct<CharT, '1', bits...>
            {
               static constexpr CharT value{
                  static_cast<CharT>(1 << sizeof...(bits)) |
                  binary_struct<CharT, bits...>::value };
            };

            template <typename CharT>
            struct binary_struct<CharT>
            {
               static constexpr CharT value{ 0 };
            };
         }

         template<char... bits>
         constexpr byte8 operator""_b8()
         {
            static_assert(
               sizeof...(bits) <= 8,
               "binary literal b8 must be up to 8 digits long");

            return binary_literals_internals::binary_struct<byte8, bits...>::value;
         }

         template<char... bits>
         constexpr byte16 operator""_b16()
         {
            static_assert(
               sizeof...(bits) <= 16,
               "binary literal b16 must be up to 16 digits long");

            return binary_literals_internals::binary_struct<byte16, bits...>::value;
         }

         template<char... bits>
         constexpr byte32 operator""_b32()
         {
            static_assert(
               sizeof...(bits) <= 32,
               "binary literal b32 must be up to 32 digits long");

            return binary_literals_internals::binary_struct<byte32, bits...>::value;
         }

      }
   }

   void execute()
   {
      using namespace binary;
      using namespace binary_literals;

      using namespace binary;
      using namespace binary_literals;

      auto b1 = 1010_b8;
      auto b2 = 101010101010_b16;
      auto b3 = 10101010101010101010101_b32;

      // binary literal b8 must be up to 8 digits long
      //auto b4 = 0011111111_b8;

      // binary literal b16 must be up to 16 digits long
      //auto b5 = 001111111111111111_b16;

      // binary literal b32 must be up to 32 digits long
      //auto b6 = 0011111111111111111111111111111111_b32;
   }
}