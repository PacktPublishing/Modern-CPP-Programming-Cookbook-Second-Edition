#pragma once

#include <ostream>

class point3d
{
   int x_;
   int y_;
   int z_;
public:
   point3d(
      int const x = 0, 
      int const y = 0, 
      int const z = 0):x_(x), y_(y), z_(z) {}

   int      x() const      { return x_; }
   point3d& x(int const x) { x_ = x; return *this; }
   int      y() const      { return y_; }
   point3d& y(int const y) { y_ = y; return *this; }
   int      z() const      { return z_; }
   point3d& z(int const z) { z_ = z; return *this; }

   bool operator==(point3d const & pt) const
   {
      return x_ == pt.x_ && y_ == pt.y_ && z_ == pt.z_;
   }
   
   bool operator!=(point3d const & pt) const
   {
      return !(*this == pt);
   }

   bool operator<(point3d const & pt) const
   {
      return x_ < pt.x_ || y_ < pt.y_ || z_ < pt.z_;
   }

   friend std::ostream& operator<<(std::ostream& stream, point3d const & pt)
   {
      stream << "(" << pt.x_ << "," << pt.y_ << "," << pt.z_ << ")";
      return stream;
   }

   void offset(int const offsetx, int const offsety, int const offsetz)
   {
      x_ += offsetx;
      y_ += offsety;
      z_ += offsetz;
   }

   static point3d origin() { return point3d{}; }
};