#pragma once

#include <variant>
#include <iostream>
#include <string>
#include <vector>
#include <type_traits>
#include <iomanip>
#include <chrono>
#include <algorithm>

namespace recipe_6_09
{
   using namespace std::string_literals;

   template <typename CharT>
   using tstring = std::basic_string<CharT, std::char_traits<CharT>, std::allocator<CharT>>;

   template<typename CharT>
   inline tstring<CharT> to_upper(tstring<CharT> text)
   {
      std::transform(std::begin(text), std::end(text), std::begin(text), toupper);
      return text;
   }

   enum class Genre { Drama, Action, SF, Comedy };

   struct Movie
   {
      std::string title;
      std::chrono::minutes length;
      std::vector<Genre> genre;
   };

   struct Track
   {
      std::string title;
      std::chrono::seconds length;
   };

   struct Music
   {
      std::string title;
      std::string artist;
      std::vector<Track> tracks;
   };

   struct Software
   {
      std::string title;
      std::string vendor;
   };

   using dvd = std::variant<Movie, Music, Software>;

   void execute()
   {
      {
         using namespace std::chrono_literals;

         std::vector<dvd> dvds
         {
            Movie{ "The Matrix"s, 2h + 16min,{ Genre::Action, Genre::SF } },
            Music{ "The Wall"s, "Pink Floyd"s,{ { "Mother"s, 5min + 32s },{ "Another Brick in the Wall"s, 9min + 8s } } },
            Software{ "Windows"s, "Microsoft"s },
         };

         // void visitor
         for (auto const & d : dvds)
         {
            std::visit(
               [](auto&& arg) 
                  {std::cout << arg.title << '\n'; }, 
               d);
         }

         // value returning visitor
         for (auto const & d : dvds)
         {
            dvd result = std::visit(
               [](auto&& arg) -> dvd
                  { 
                     auto cpy{ arg }; 
                     cpy.title = to_upper(cpy.title);
                     return cpy; 
                  },
               d);

            std::visit(
               [](auto&& arg) 
                  {std::cout << arg.title << '\n'; }, 
               result);
         }

         struct visitor_functor
         {
            void operator()(Movie const & arg) const
            {
               std::cout << "Movie" << '\n';
               std::cout << "  Title: " << arg.title << '\n';
               std::cout << "  Length: " << arg.length.count() << "min" << '\n';
            }

            void operator()(Music const & arg) const
            {
               std::cout << "Music" << '\n';
               std::cout << "  Title: " << arg.title << '\n';
               std::cout << "  Artist: " << arg.artist << '\n';
               for (auto const & t : arg.tracks)
                  std::cout << "    Track: " << t.title
                  << ", " << t.length.count() << "sec" << '\n';
            }

            void operator()(Software const & arg) const
            {
               std::cout << "Software" << '\n';
               std::cout << "  Title: " << arg.title << '\n';
               std::cout << "  Vendor: " << arg.vendor << '\n';
            }
         };

         for (auto const & d : dvds)
         {
            std::visit(visitor_functor(), d);
         }

#ifdef CONSTEXPR_IF_AVAILABLE
         for (auto const & d : dvds)
         {
            std::visit([](auto&& arg) {
               using T = std::decay_t<decltype(arg)>;
               if constexpr (std::is_same_v<T, Movie>)
               {
                  std::cout << "Movie" << '\n';
                  std::cout << "  Title: " << arg.title << '\n';
                  std::cout << "  Length: " << arg.length.count() << "min" << '\n';
               }
               else if constexpr (std::is_same_v<T, Music>)
               {
                  std::cout << "Music" << '\n';
                  std::cout << "  Title: " << arg.title << '\n';
                  std::cout << "  Artist: " << arg.artist << '\n';
                  for (auto const & t : arg.tracks)
                     std::cout << "    Track: " << t.title
                     << ", " << t.length.count() << "sec" << '\n';
               }
               else if constexpr (std::is_same_v<T, Software>)
               {
                  std::cout << "Software" << '\n';
                  std::cout << "  Title: " << arg.title << '\n';
                  std::cout << "  Vendor: " << arg.vendor << '\n';
               }
            }, d);
         }
#endif

         /*
         Movie
         Title: The Matrix
         Length: 136min
         Music
         Title: The Wall
         Artist: Pink Floyd
         Track: Mother, 332sec
         Track: Another Brick in the Wall, 548sec
         Software
         Title: Microsoft
         Vendor: Windows
         */
      }
   }
}