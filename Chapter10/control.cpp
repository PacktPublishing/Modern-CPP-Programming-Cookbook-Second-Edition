#include "control.h"
#include <iostream>
#include <string>
#include <string_view>

namespace recipe_10_02
{
   class control_pimpl
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

   control::control() :
      pimpl(
         new control_pimpl(),
         [](control_pimpl* pimpl) {delete pimpl; })
   {}

   void control::set_text(std::string_view text)
   {
      pimpl->set_text(text);
   }

   void control::resize(int const w, int const h)
   {
      pimpl->resize(w, h);
   }

   void control::show()
   {
      pimpl->show();
   }

   void control::hide()
   {
      pimpl->hide();
   }

   control_copyable::control_copyable() :
      pimpl(
         new control_pimpl(),
         [](control_pimpl* pimpl) {delete pimpl; })
   {}

   control_copyable::control_copyable(control_copyable &&) noexcept = default;
   control_copyable& control_copyable::operator=(control_copyable &&) noexcept = default;

   control_copyable::control_copyable(const control_copyable& op)
      : pimpl(
         new control_pimpl(*op.pimpl),
         [](control_pimpl* pimpl) {delete pimpl; })
   {}

   control_copyable& control_copyable::operator=(const control_copyable& op) 
   {
      if (this != &op) 
      {
         pimpl = std::unique_ptr<control_pimpl, void(*)(control_pimpl*)>(
            new control_pimpl(*op.pimpl),
            [](control_pimpl* pimpl) {delete pimpl; });
      }
      return *this;
   }

   void control_copyable::set_text(std::string_view text)
   {
      pimpl->set_text(text);
   }

   void control_copyable::resize(int const w, int const h)
   {
      pimpl->resize(w, h);
   }

   void control_copyable::show()
   {
      pimpl->show();
   }

   void control_copyable::hide()
   {
      pimpl->hide();
   }
}