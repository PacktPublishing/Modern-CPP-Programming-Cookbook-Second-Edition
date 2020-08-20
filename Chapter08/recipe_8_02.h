#pragma once

#include <mutex>

namespace recipe_8_02
{
   class foo_rec
   {
      std::recursive_mutex m;
      int data;

   public:
      foo_rec(int const d = 0) : data(d) {}

      void update(int const d)
      {
         std::lock_guard<std::recursive_mutex> lock(m);
         data = d;
      }

      int update_with_return(int const d)
      {
         std::lock_guard<std::recursive_mutex> lock(m);
         auto temp = data;
         update(d);
         return temp;
      }
   };

   class foo
   {
      std::mutex m;
      int data;

      void internal_update(int const d) { data = d; }

      foo(int const d = 0) : data(d) {}

      void update(int const d)
      {
         std::lock_guard<std::mutex> lock(m);
         internal_update(d);
      }

      int update_with_return(int const d)
      {
         std::lock_guard<std::mutex> lock(m);
         auto temp = data;
         internal_update(d);
         return temp;
      }
   };

   void execute()
   {

   }
}