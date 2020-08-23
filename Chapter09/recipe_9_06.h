#pragma once

#include <iostream>
#include <string>

namespace recipe_9_06
{
   void old_api([[maybe_unused]] char* str, [[maybe_unused]] unsigned int size)
   {
      // do something without changing the string
   }

   class control
   {
   public:
      typedef   size_t data_type;

      void      set_data(data_type d) { data = d; }
      data_type get_data() const { return data; }

   private:
      data_type data;
   };

   class user_data
   {
   };

   enum options { one = 1, two, three };

   struct base
   {
      virtual void run() {}
      virtual ~base() {}
   };

   struct derived : public base
   {
   };

   struct struct1 {};
   struct struct2 {};

   void execute()
   {
      // static cast
      {
         int x = 42, y = 13;
         double d = static_cast<double>(x) / y;

         [[maybe_unused]] int n = static_cast<int>(d);

         int value = 1;
         [[maybe_unused]] options op = static_cast<options>(value);
      }

      // dynamic cast
      {
         derived d;
         base    b;

         [[maybe_unused]] base* pb = dynamic_cast<base*>(&d);         // OK
         [[maybe_unused]] derived* pd = dynamic_cast<derived*>(&b);   // fail

         try
         {
            [[maybe_unused]] base& rb = dynamic_cast<base&>(d);       // OK
            [[maybe_unused]] derived& rd = dynamic_cast<derived&>(b); // fail
         }
         catch (std::bad_cast const& e)
         {
            std::cout << e.what() << '\n';
         }

         // struct1 s1;
         // struct2* ps2 = dynamic_cast<struct2*>(&s1); // error
      }

      // const cast
      {
         std::string str{ "sample" };
         old_api(const_cast<char*>(str.c_str()),
            static_cast<unsigned int>(str.size()));

         // undefined behavior
         int const a = 42;
         int const* p = &a;
         int* q = const_cast<int*>(p);
         *q = 0;
      }

      // reinterpret cast
      {
         control c;

         user_data* ud = new user_data();
         c.set_data(reinterpret_cast<control::data_type>(ud));

         [[maybe_unused]] user_data* ud2 = reinterpret_cast<user_data*>(c.get_data());

         // undefined behavior
         int* pi = new int{ 42 };
         [[maybe_unused]] double* pd = reinterpret_cast<double*>(pi);
      }
   }
}