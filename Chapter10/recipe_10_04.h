#pragma once

#include <iostream>
#include <vector>
#include <memory>

namespace recipe_10_04
{
   class control
   {
   private:
      virtual void paint() = 0;

   protected:
      virtual void initialize_impl()
      {
         std::cout << "initializing control..." << '\n';
      }

      virtual void erase_background()
      {
         std::cout << "erasing control background..." << '\n';
      }

   public:
      void draw()
      {
         erase_background();
         paint();
      }

      void initialize()
      {
         initialize_impl();
      }

      virtual ~control()
      {
         std::cout << "destroying control..." << '\n';
      }
   };

   class button : public control
   {
   private:
      virtual void paint() override
      {
         std::cout << "painting button..." << '\n';
      }

   protected:
      virtual void initialize_impl()
      {
         control::initialize_impl();
         std::cout << "initializing button..." << '\n';
      }

      virtual void erase_background() override
      {
         control::erase_background();
         std::cout << "erasing button background..." << '\n';
      }

   public:
      ~button()
      {
         std::cout << "destroying button..." << '\n';
      }
   };

   class checkbox : public button
   {
   private:
      virtual void paint() override
      {
         std::cout << "painting checkbox..." << '\n';
      }

   protected:
      virtual void erase_background() override
      {
         button::erase_background();
         std::cout << "erasing checkbox background..." << '\n';
      }

   public:
      ~checkbox()
      {
         std::cout << "destroying checkbox..." << '\n';
      }
   };

   void execute()
   {
      {
         std::vector<std::unique_ptr<control>> controls;

         controls.emplace_back(std::make_unique<button>());
         controls.emplace_back(std::make_unique<checkbox>());

         for (auto& c : controls)
            c->draw();
      }

      {
         button b;
         b.initialize();
         b.draw();
      }
   }
}