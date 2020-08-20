#pragma once

#include <string>
#include <string_view>

namespace recipe_10_03
{
   class control;

   class control_properties
   {
      int id_;
      std::string text_;
      int width_ = 0;
      int height_ = 0;
      bool visible_ = false;

      friend class control;
   public:
      control_properties(int const id) :id_(id)
      {}

      control_properties& text(std::string_view t) 
      { text_ = t.data(); return *this; }

      control_properties& width(int const w) 
      { width_ = w; return *this; }

      control_properties& height(int const h) 
      { height_ = h; return *this; }

      control_properties& visible(bool const v) 
      { visible_ = v; return *this; }
   };

   class control
   {
      int id_;
      std::string text_;
      int width_;
      int height_;
      bool visible_;

   public:
      control(
         int const id,
         std::string_view text = "",
         int const width = 0,
         int const height = 0,
         bool const visible = false):
         id_(id), text_(text), 
         width_(width), height_(height), 
         visible_(visible)
      {}

      control(control_properties const & cp):
         id_(cp.id_), 
         text_(cp.text_),
         width_(cp.width_), 
         height_(cp.height_),
         visible_(cp.visible_)
      {}
   };

   void execute()
   {
      {
         control c(1044, "sample", 100, 20, true);
      }

      {
         control c(
            control_properties(1044)
               .visible(true)
               .height(20)
               .width(100));
      }
   }
}