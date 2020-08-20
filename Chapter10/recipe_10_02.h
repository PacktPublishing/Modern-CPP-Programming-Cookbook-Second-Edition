#pragma once

#include <iostream>
#include <string>
#include <string_view>
#include <iomanip>

#include "control.h"

namespace recipe_10_02
{
   class oldcontrol
   {
      std::string text;
      int width = 0;
      int height = 0;
      bool visible = true;

      void draw()
      {
         std::cout 
            << "control " << '\n'
            << "  visible: " << std::boolalpha << visible << std::noboolalpha << '\n'
            << "  size: " << width << ", " << height << '\n'
            << "  text: " << text << '\n';
      }
   public:
      void set_text(std::string_view t)
      {
         text = t.data();
         draw();
      }

      void resize(int const w, int const h)
      {
         width = w;
         height = h;
         draw();
      }

      void show() 
      { 
         visible = true; 
         draw();
      }

      void hide() 
      { 
         visible = false; 
         draw();
      }
   };

   void execute()
   {
      {
         oldcontrol c;
         c.resize(100, 20);
         c.set_text("sample");
         c.hide();

         oldcontrol c2 = c;
         c2.show();

         oldcontrol c3 = std::move(c2);
         c3.hide();
      }

      {
         control c;
         c.resize(100, 20);
         c.set_text("sample");
         c.hide();

         control c2 = std::move(c);
         c2.show();
      }

      {
         control_copyable c;
         c.resize(100, 20);
         c.set_text("sample");
         c.hide();

         control_copyable c2 = c;
         c2.show();

         control_copyable c3 = std::move(c2);
         c3.hide();
      }
   }
}