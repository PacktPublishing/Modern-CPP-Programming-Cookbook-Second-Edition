#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <iomanip>
#include <cassert>

namespace recipe_9_08
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

      void print() { std::cout << "Derived" << '\n'; }
   };

   struct Apprentice;

   struct Master : std::enable_shared_from_this<Master>
   {
      ~Master() { std::cout << "~Master" << '\n'; }

      void take_apprentice(std::shared_ptr<Apprentice> a);
   private:
      std::shared_ptr<Apprentice> apprentice;
   };

   struct Apprentice
   {
      ~Apprentice() { std::cout << "~Apprentice" << '\n'; }

      void take_master(std::weak_ptr<Master> m);
   private:
      std::weak_ptr<Master> master;
   };

   void Master::take_apprentice(std::shared_ptr<Apprentice> a)
   {
      apprentice = a;
      apprentice->take_master(shared_from_this());
   }

   void Apprentice::take_master(std::weak_ptr<Master> m)
   {
      master = m;
   }

   void execute()
   {
      // constructors
      {
         std::shared_ptr<int> pnull1;
         std::shared_ptr<int> pnull2(nullptr);

         std::shared_ptr<int> pi1(new int(42));
         std::shared_ptr<int> pi2 = pi1;

         assert(pi1.use_count() == 2);

         std::shared_ptr<foo> pf1(new foo());
         pf1->print();

         std::shared_ptr<foo> pf2(new foo(42, 42.0, "42"));
         pf2->print();
      }

      // make_shared
      {
         std::shared_ptr<int> pi = std::make_shared<int>(42);
         std::shared_ptr<foo> pf1 = std::make_shared<foo>();
         pf1->print();
         std::shared_ptr<foo> pf2 = std::make_shared<foo>(42, 42.0, "42");
         pf2->print();
      }

      // custom deleter
      {
         std::shared_ptr<foo> pf1(
            new foo(42, 42.0, "42"),
            foo_deleter());

         std::shared_ptr<foo> pf2(
            new foo(42, 42.0, "42"),
            [](foo* p) {
            std::cout << "deleting foo from lambda..." << '\n';
            delete p;
         });
      }

      // arrays
      {
         std::shared_ptr<int> pa1(
            new int[3]{ 1, 2, 3 },
            std::default_delete<int[]>());

         std::shared_ptr<int> pa2(
            new int[3]{ 1, 2, 3 },
            [](int* p) {delete[] p; });
      }

      // array element access
      {
         std::shared_ptr<int[]> pa1(
            new int[3]{ 1, 2, 3 },
            std::default_delete<int[]>());

         for (int i = 0; i < 3; ++i)
            pa1[i] *= 2;
      }

      // dereferencing
      {
         std::shared_ptr<int> pi = std::make_shared<int>(42);
         *pi = 21;

         std::shared_ptr<foo> pf = std::make_shared<foo>(42, 42.0, "42");
         pf->print();
      }

      // empty check
      {
         std::shared_ptr<int> pnull;
         if (pnull) std::cout << "not null" << '\n';

         std::shared_ptr<int> pi(new int(42));
         if (pi) std::cout << "not null" << '\n';
      }

      // get
      {
         std::shared_ptr<int> pi;
         func(pi.get());

         pi = std::make_shared<int>(42);
         func(pi.get());
      }

      // container storing
      {
         std::vector<std::shared_ptr<foo>> data;
         for (int i = 0; i < 5; i++)
            data.push_back(
               std::make_shared<foo>(i, i, std::to_string(i)));

         auto pf = std::make_shared<foo>(42, 42.0, "42");

         data.push_back(std::move(pf));
         assert(!pf);

         for (auto const & p : data)
            p->print();
      }


      // conversion 
      {
         std::shared_ptr<Derived> pd = std::make_shared<Derived>();
         std::shared_ptr<Base>    pb = pd;

         std::static_pointer_cast<Derived>(pb)->print();
      }

      // weak pointer
      {
         auto sp1 = std::make_shared<int>(42);
         assert(sp1.use_count() == 1);

         std::weak_ptr<int> wpi = sp1;
         assert(sp1.use_count() == 1);

         auto sp2 = wpi.lock();
         assert(sp1.use_count() == 2);
         assert(sp2.use_count() == 2);

         sp1.reset();
         assert(sp1.use_count() == 0);
         assert(sp2.use_count() == 1);
      }

      // enable_shared_from_this
      {
         auto m = std::make_shared<Master>();
         auto a = std::make_shared<Apprentice>();

         m->take_apprentice(a);
      }

#ifdef HAS_FOR_OVERWRITE
      {
         std::shared_ptr<int> pi = std::make_shared_for_overwrite<int>();
         std::shared_ptr<foo[]> pa = std::make_shared_for_overwrite<foo[]>(3);
      }
#endif
   }
}