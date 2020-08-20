#pragma once

#include <any>
#include <vector>
#include <string>
#include <chrono>
#include <ctime>
#include <iomanip>

namespace recipe_6_06
{
   using namespace std::string_literals;

   void log(std::any const & value)
   {
      if (value.has_value())
      {
         auto const & tv = value.type();
         if (tv == typeid(int))
         {
            std::cout << std::any_cast<int>(value) << '\n';
         }
         else if (tv == typeid(std::string))
         {
            std::cout << std::any_cast<std::string>(value) << '\n';
         }
         else if (tv == typeid(std::chrono::time_point<std::chrono::system_clock>))
         {
            auto t = std::any_cast<std::chrono::time_point<std::chrono::system_clock>>(value);
            auto now = std::chrono::system_clock::to_time_t(t);
            std::cout << std::put_time(std::localtime(&now), "%F %T") << '\n';
         }
         else
         {
            std::cout << "unexpected value type" << '\n';
         }
      }
      else
      {
         std::cout << "(empty)" << '\n';
      }
   }

   inline bool is_integer(std::any const & a)
   {
      return a.type() == typeid(int);
   }

   void execute()
   {
      {
         std::any value(42);  // integer     42
         value = 42.0;        // double      42.0
         value = "42"s;       // std::string "42"
      }

      {
         auto ltest = [](std::any const & a) {
            if (a.has_value())
               std::cout << "has value" << '\n';
            else
               std::cout << "no value" << '\n';
         };

         std::any value;
         ltest(value);   // no value
         value = 42;
         ltest(value);   // has value
         value.reset();
         ltest(value);   // no value
      }

      {
         std::any value = 42.0;

         try
         {
            auto d = std::any_cast<double>(value);
            std::cout << d << '\n';
         }
         catch (std::bad_any_cast const & e)
         {
            std::cout << e.what() << '\n';
         }

         try
         {
            auto pd = std::any_cast<double>(&value);
            std::cout << *pd << '\n';
         }
         catch (std::bad_any_cast const & e)
         {
            std::cout << e.what() << '\n';
         }

         try
         {
            auto i = std::any_cast<int>(value);
            std::cout << i << '\n';
         }
         catch (std::bad_any_cast const & e)
         {
            std::cout << e.what() << '\n';
         }


         value = "sample"s;
         try
         {
            auto s = std::any_cast<std::string>(value);
            std::cout << s << '\n';
         }
         catch (std::bad_any_cast const & e)
         {
            std::cout << e.what() << '\n';
         }

         value = std::vector<int>{ 1, 1, 2, 3, 5, 8 };
         try
         {
            auto v = std::any_cast<std::vector<int>>(value);
            for (auto e : v)
               std::cout << e << '\n';
         }
         catch (std::bad_any_cast const & e)
         {
            std::cout << e.what() << '\n';
         }
      }

      {
         log(std::any{});// (empty)
         log(42);        // 42
         log("42"s);     // 42
         log(42.0);      // unexpected value type
         log(std::chrono::system_clock::now());  // 2016-10-30 22:42:57
      }

      {
         std::vector<std::any> values;
         values.push_back(std::any{});
         values.push_back(42);
         values.push_back("42"s);
         values.push_back(42.0);
         values.push_back(std::chrono::system_clock::now());

         for (auto const v : values)
            log(v);
      }

      {
         struct foo
         {
            foo() = default;
            foo(foo const&) = delete;
         };

         [[maybe_unused]] foo f;
         // std::any value = f; // error
      }
   }
}
