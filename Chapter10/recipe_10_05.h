#pragma once

#include <iostream>

namespace recipe_10_05
{
   namespace oldversion
   {
      class Client
      {
         int data_1;
         int data_2;

         void action1() {}
         void action2() {}

         friend class Friend;
      public:
         // public interface
      };

      class Friend
      {
      public:
         void access_client_data(Client& c)
         {
            c.action1();
            c.action2();
            auto d1 = c.data_1;
            auto d2 = c.data_1;
         }
      };
   }

   class Client
   {
      int data_1;
      int data_2;

      void action1() {}
      void action2() {}

      friend class Attorney;
   public:
      // public interface
   };

   class Attorney
   {
      static inline void run_action1(Client& c)
      {
         c.action1();
      }

      static inline int get_data1(Client& c)
      {
         return c.data_1;
      }

      friend class Friend;
   };

   class Friend
   {
   public:
      void access_client_data(Client& c)
      {
         Attorney::run_action1(c);
         auto d1 = Attorney::get_data1(c);
      }
   };

   class B
   {
      virtual void execute() { std::cout << "base" << '\n'; }

      friend class BAttorney;
   };

   class D : public B
   {
      virtual void execute() override { std::cout << "derived" << '\n'; }
   };

   class BAttorney
   {
      static inline void execute(B& b)
      {
         b.execute();
      }

      friend class F;
   };

   class F
   {
   public:
      void run()
      {
         B b;
         BAttorney::execute(b); // prints 'base'

         D d;
         BAttorney::execute(d); // prints 'derived'
      }
   };

   void execute()
   {
      {
         oldversion::Client c;
         oldversion::Friend f;
         f.access_client_data(c);
      }

      {
         Client c;
         Friend f;
         f.access_client_data(c);
      }

      {
         F f;
         f.run();
      }
   }
}