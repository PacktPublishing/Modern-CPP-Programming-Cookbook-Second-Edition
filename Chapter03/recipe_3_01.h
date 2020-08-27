#pragma once

#include <utility>

namespace recipe_3_01
{
   class foo_not_copiable
   {
   public:
      foo_not_copiable() {};
   private:
      foo_not_copiable(foo_not_copiable const&);
      foo_not_copiable& operator=(foo_not_copiable const&);
   };

   class bar_not_copiable
   {
   public:
      bar_not_copiable() = default;

      bar_not_copiable(bar_not_copiable const &) = delete;
      bar_not_copiable& operator=(bar_not_copiable const&) = delete;
   };

   struct Data {};

   class data_wrapper
   {
      Data* data;
   public:
      data_wrapper(Data* d = nullptr) : data(d) {}
      ~data_wrapper() { delete data; }

      data_wrapper(data_wrapper const&) = delete;
      data_wrapper& operator=(data_wrapper const &) = delete;

      data_wrapper(data_wrapper&& other) :data(std::move(other.data)) 
      { 
         other.data = nullptr; 
      }

      data_wrapper& operator=(data_wrapper&& other)
      {
         if (this != std::addressof(other))
         {
            delete data;
            data = std::move(other.data);
            other.data = nullptr;
         }

         return *this;
      }
   };

   class foo
   {
   public:
      foo() = default;

      inline foo& operator=(foo const &);
   };

   inline foo& foo::operator=(foo const &) = default;

   //void forward_declared_function();

   // ...

   //void forward_declared_function() = delete; // error

   template <typename T>
   void run(T) = delete;
   void run(long) {}

   void execute()
   {
      {
         //foo_not_copiable f1, f2;
         //foo_not_copiable f3 = f1; // error
         //f1 = f2; // error
      }
      
      {
         //bar_not_copiable f1, f2;
         //foo_not_copiable f3 = f1; // error
         //f1 = f2; // error         
      }

      {
         //run(42); // error
         run(42L);  // OK
      }
   }
}