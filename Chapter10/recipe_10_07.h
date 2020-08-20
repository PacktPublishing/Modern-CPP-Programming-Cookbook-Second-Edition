#pragma once

namespace recipe_10_07
{
   class Singleton
   {
   private:
      Singleton() {}
   public:
      Singleton(Singleton const &) = delete;
      Singleton& operator=(Singleton const&) = delete;

      static Singleton& instance()
      {
         static Singleton single;
         return single;
      }
   };

   template <class T>
   class SingletonBase
   {
   protected:
      SingletonBase() {}
   public:
      SingletonBase(SingletonBase const &) = delete;
      SingletonBase& operator=(SingletonBase const&) = delete;

      static T& instance()
      {
         static T single;
         return single;
      }
   };

   class Single : public SingletonBase<Single>
   {
      Single() {}
      friend class SingletonBase<Single>;
   public:
      void demo() { std::cout << "demo" << '\n'; }
   };

   void execute()
   {
      {
         auto& s = Singleton::instance();
      }

      {
         auto& s = Single::instance();
         s.demo();
      }
   }
}