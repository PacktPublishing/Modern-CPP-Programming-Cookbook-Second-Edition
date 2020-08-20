#pragma once

#include <string>
#include <map>
#include <vector>
#include <mutex>

namespace recipe_9_03
{
   struct session {};

   session connect(std::string const & uri, int const timeout = 2000)
   {
      /* do something */
      return session{ /* ... */ };
   }

   class contact {};

   class addressbook
   {
      std::vector<contact> contacts;
   public:
      contact&        operator[](size_t const index)
      {
         throw std::runtime_error("not implemented");
      }
      contact const & operator[](size_t const index) const
      {
         throw std::runtime_error("not implemented");
      }
   };

   class user_settings
   {
      bool show_online;
   public:
      bool can_show_online() const { return show_online; }

      int const min_update_interval = 15;

      /* other members */
   };

   user_settings get_user_settings()
   {
      return user_settings{};
   }

   void update()
   {
      user_settings const us = get_user_settings();

      if (us.can_show_online()) { /* do something */ }

      /* do more */
   }

   class computation
   {
      double compute_value(double const input) const
      {
         /* long running operation */
         return input;
      }

      mutable std::map<double, double> cache;
   public:
      double compute(double const input) const
      {
         auto it = cache.find(input);
         if (it != cache.end()) return it->second;

         auto result = compute_value(input);
         cache[input] = result;

         return result;
      }
   };

   template <typename T>
   class container
   {
      std::vector<T>     data;
      mutable std::mutex mt;
   public:
      void add(T const & value)
      {
         std::lock_guard<std::mutex> lock(mt);
         data.push_back(value);
      }

      bool contains(T const & value) const
      {
         std::lock_guard<std::mutex> lock(mt);
         return std::find(std::begin(data), std::end(data), value)
            != std::end(data);
      }
   };

   void execute()
   {
      update();

      {
         computation const c;
         c.compute(42);
      }

      {
         container<int> c;
         c.add(42);
         auto exists = c.contains(42);
      }
      /*
      int const c = 42;
      int* x;
      int const ** p = &x; // this is an error
      *p = &c;
      *x = 0;              // oops, this modifies c
      */
   }
}