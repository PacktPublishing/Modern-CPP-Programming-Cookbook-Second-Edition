#pragma once

#include <memory>
#include <string>
#include <string_view>

namespace recipe_10_02
{
   class control_pimpl;

   class control
   {
      std::unique_ptr<control_pimpl, void(*)(control_pimpl*)> pimpl;

   public:
      control();
      void set_text(std::string_view text);
      void resize(int const w, int const h);
      void show();
      void hide();
   };

   class control_copyable
   {
      std::unique_ptr<control_pimpl, void(*)(control_pimpl*)> pimpl;

   public:
      control_copyable();

      control_copyable(control_copyable && op) noexcept;
      control_copyable& operator=(control_copyable && op) noexcept;

      control_copyable(const control_copyable& op);
      control_copyable& operator=(const control_copyable& op);

      void set_text(std::string_view text);
      void resize(int const w, int const h);
      void show();
      void hide();
   };
}