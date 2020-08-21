#pragma once

#include <memory>

namespace recipe_4_05
{
   namespace v1
   {
      template <typename T>
      auto value_of(T value)
      {
         if constexpr (std::is_pointer_v<T>)
            return *value;
         else
            return value;
      }
   }

   namespace v2
   {
      template <typename T, 
                typename = typename std::enable_if_t<std::is_pointer_v<T>, T>>
      auto value_of(T value)
      {
         return *value;
      }

      template <typename T, 
                typename = typename std::enable_if_t<!std::is_pointer_v<T>, T>>
      T value_of(T value)
      {
         return value;
      }
   }

   namespace binary
   {
      using byte8 = unsigned char;
      using byte16 = unsigned short;
      using byte32 = unsigned int;

      namespace binary_literals
      {
         namespace binary_literals_internals
         {
            template <typename CharT, char d, char... bits>
            constexpr CharT binary_eval()
            {
               if constexpr(sizeof...(bits) == 0)
                  return static_cast<CharT>(d - '0');
               else if constexpr(d == '0')
                  return binary_eval<CharT, bits...>();
               else if constexpr(d == '1')
                  return static_cast<CharT>((1 << sizeof...(bits)) | binary_eval<CharT, bits...>());
            }
         }

         template<char... bits>
         constexpr byte8 operator""_b8()
         {
            static_assert(
               sizeof...(bits) <= 8,
               "binary literal b8 must be up to 8 digits long");

            return binary_literals_internals::binary_eval<byte8, bits...>();
         }

         template<char... bits>
         constexpr byte16 operator""_b16()
         {
            static_assert(
               sizeof...(bits) <= 16,
               "binary literal b16 must be up to 16 digits long");

            return binary_literals_internals::binary_eval<byte16, bits...>();
         }

         template<char... bits>
         constexpr byte32 operator""_b32()
         {
            static_assert(
               sizeof...(bits) <= 32,
               "binary literal b32 must be up to 32 digits long");

            return binary_literals_internals::binary_eval<byte32, bits...>();
         }
      }
   }

   void execute()
   {
      {
         using namespace v1;
         [[maybe_unused]] auto v1 = value_of(42);

         auto p = std::make_unique<int>(42);
         [[maybe_unused]] auto v2 = value_of(p.get());
      }

      {
         using namespace v2;
         [[maybe_unused]] auto v1 = value_of(42);

         auto p = std::make_unique<int>(42);
         [[maybe_unused]] auto v2 = value_of(p.get());
      }

      {
         using namespace binary;
         using namespace binary_literals;

         [[maybe_unused]] auto b1 = 1010_b8;
         [[maybe_unused]] auto b2 = 101010101010_b16;
         [[maybe_unused]] auto b3 = 010101010101010101010101_b32;
      }
   }
}