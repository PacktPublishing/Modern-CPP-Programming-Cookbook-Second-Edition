#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <iomanip>
#include <cassert>

namespace recipe_9_07
{
   class foo
   {
      int         a;
      double      b;
      std::string c;
   public:
      foo(int const a = 0, double const b = 0, std::string const & c = "") :
         a(a), b(b), c(c) {}

      void print() const
      {
         std::cout << '(' << a << ',' << b << ',' << std::quoted(c) << ')' << '\n';
      }
   };

   struct foo_deleter
   {
      void operator()(foo* pf) const
      {
         std::cout << "deleting foo..." << '\n';
         delete pf;
      }
   };

   void func(int* ptr)
   {
      if (ptr != nullptr)
         std::cout << *ptr << '\n';
      else
         std::cout << "null" << '\n';
   }

   void some_function(std::unique_ptr<foo> p)
   {
   }

   void some_other_function(std::unique_ptr<foo> p, int const v)
   {
   }

   int function_that_throws()
   {
      throw std::runtime_error("not implemented");
   }

   struct Base
   {
      virtual ~Base() 
      {
         std::cout << "~Base()" << '\n';
      }
   };

   struct Derived : public Base
   {
      virtual ~Derived()
      {
         std::cout << "~Derived()" << '\n';
      }
   };

   void execute()
   {
      {
         std::unique_ptr<int> pnull;

         std::unique_ptr<int> pi(new int(42));

         std::unique_ptr<int[]> pa(new int[3]{ 1,2,3 });

         std::unique_ptr<foo> pf(new foo(42, 42.0, "42"));
      }

      {
         std::unique_ptr<int> pi = std::make_unique<int>(42);

         std::unique_ptr<int[]> pa = std::make_unique<int[]>(3);

         std::unique_ptr<foo> pf = std::make_unique<foo>(42, 42.0, "42");
      }

      {
         std::unique_ptr<int[]> pa = std::make_unique<int[]>(3);
         for (int i = 0; i < 3; ++i)
            pa[i] = i + 1;

         for (int i = 0; i < 3; ++i)
            std::cout << pa[i] << '\n';
      }

      {
         std::unique_ptr<int> pnull;
         if (pnull) std::cout << "not null" << '\n';

         std::unique_ptr<int> pi(new int(42));
         if (pi) std::cout << "not null" << '\n';
      }

      {
         auto pi = std::make_unique<int>(42);

         auto qi = std::move(pi);
         assert(pi.get() == nullptr);
         assert(qi.get() != nullptr);
      }

      {
         auto pi = std::make_unique<int>(42);
         *pi = 21;

         auto pf1 = std::make_unique<foo>();
         pf1->print();

         auto pf2 = std::make_unique<foo>(42, 42.0, "42");
         pf2->print();
      }

      {
         std::vector<std::unique_ptr<foo>> data;
         for (int i = 0; i < 5; i++)
            data.push_back(
               std::make_unique<foo>(i, i, std::to_string(i)));

         auto pf = std::make_unique<foo>(42, 42.0, "42");

         data.push_back(std::move(pf));

         for (auto const & p : data)
            p->print();
      }

      {
         std::unique_ptr<int> pi;
         func(pi.get());

         pi = std::make_unique<int>(42);
         func(pi.get());
      }

      {
         std::unique_ptr<foo, foo_deleter> pf(
            new foo(42, 42.0, "42"),
            foo_deleter());
      }

      {
         some_function(std::unique_ptr<foo>(new foo()));
         some_function(std::make_unique<foo>());
      }

      {
         try
         {
            some_other_function(std::unique_ptr<foo>(new foo()), function_that_throws());
         }
         catch (...) {}

         try
         {
            some_other_function(std::make_unique<foo>(), function_that_throws());
         }
         catch (...) {}
      }

      {
         std::unique_ptr<Derived> pd = std::make_unique<Derived>();
         std::unique_ptr<Base>    pb = std::move(pd);
      }

#ifdef HAS_FOR_OVERWRITE
      {
         std::unique_ptr<int>   pi = std::make_unique_for_overwrite<int>();
         std::unique_ptr<int[]> pa = std::make_unique_for_overwrite<int[]>();
      }
#endif
   }
}