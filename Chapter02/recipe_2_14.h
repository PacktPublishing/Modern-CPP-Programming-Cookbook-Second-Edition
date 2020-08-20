#pragma once

namespace recipe_2_14
{
   namespace v1
   {
      struct employee
      {
         int         id;
         std::string firstName;
         std::string lastName;
      };
   }

   namespace v2
   {
      struct employee
      {
         int         id;
         std::string firstName;
         std::string lastName;
      };
   }
}

#ifdef HAS_FORMAT_LIBRARY
template <>
struct std::formatter<recipe_2_14::v1::employee>
{
   constexpr auto parse(format_parse_context& ctx)
   {
      return ctx.begin();
   }

   auto format(recipe_2_14::v1::employee const& value, format_context& ctx) {
      return std::format_to(ctx.out(),
         "[{}] {} {}",
         e.id, e.firstName, e.lastName);
   }
};

template<>
struct std::formatter<recipe_2_14::v2::employee>
{
   bool lexicographic_order = false;

   template <typename ParseContext>
   constexpr auto parse(ParseContext& ctx)
   {
      auto iter = ctx.begin();
      auto get_char = [&]() { return iter != ctx.end() ? *iter : 0; };

      if (get_char() == ':') ++iter;
      char c = get_char();

      switch (c)
      {
      case '}': return ++iter;
      case 'L': lexicographic_order = true; return ++iter;
      case '{': return ++iter;
      default: throw std::format_error("invalid format");
      }
   }

   template <typename FormatContext>
   auto format(recipe_2_14::v2::employee const& e, FormatContext& ctx)
   {
      if (lexicographic_order)
         return std::format_to(ctx.out(), "[{}] {}, {}", e.id, e.lastName, e.firstName);

      return std::format_to(ctx.out(), "[{}] {} {}", e.id, e.firstName, e.lastName);
   }
};
#endif

namespace recipe_2_14
{
   void execute()
   {
#ifdef HAS_FORMAT_LIBRARY
      {
         v1::employee e{ 42, "John", "Doe" };
         auto s1 = std::format("{}", e);   // [42] John Doe
         auto s2 = std::format("{:L}", e); // error
      }

      {
         v2::employee e{ 42, "John", "Doe" };
         auto s1 = std::format("{}", e);   // [42] John Doe
         auto s2 = std::format("{:L}", e); // [42] Doe, John
         auto s3 = std::format("{:A}", e); // error (invalid format)
      }
#endif
   }
}