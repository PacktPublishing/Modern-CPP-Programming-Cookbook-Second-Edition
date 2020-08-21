#pragma once

namespace recipe_1_07
{
   void execute()
   {
      {
#if defined(_WIN64)
         typedef __int64 int_ptr;
#else
         typedef int int_ptr;
#endif

         class Base
         {
         public:
            virtual void foo(int_ptr const a) {}
         };

         class Derived : public Base
         {
         public:
            virtual void foo(int const a) {}
         };
      }

      {
         class Base
         {
            virtual void foo() = 0;
            virtual void bar() {}
            virtual void foobar() = 0;
         };

         class Derived1 : public Base
         {
            virtual void foo() override = 0;
            virtual void bar() override {}
            virtual void foobar() override {}
         };

         class Derived2 : public Derived1
         {
            virtual void foo() override {}
         };
      }

      {
         class Base
         {
         public:
            virtual void foo() {}
            virtual void bar() {}
         };

         class Derived1 : public Base
         {
         public:
            void foo() override {} // for readability should also use the virtual keyword
            //virtual void bar(char const c) override {} // error, no Base::bar(char const)
         };

         class Derived2 : public Derived1
         {
            virtual void foo() final {}
         };

         class Derived3 : public Derived2
         {
            //virtual void foo() override {} // error
         };

         class Derived4 final : public Derived1
         {
            virtual void foo() override {}
         };

         //class Derived5 : public Derived4 // error
         //{
         //};
      }

      {
         class foo
         {
            int final = 0;
            void override() {}
         };
      }
   }
}