export module geometry;

import std.core;

export template <class T,
   typename = typename std::enable_if_t<std::is_arithmetic_v<T>, T>>
   struct point
{
   T x;
   T y;
};

export using int_point = point<int>;

export constexpr int_point int_point_zero{ 0,0 };

export template <class T>
double distance(point<T> const& p1,
   point<T> const& p2)
{
   return std::sqrt((p2.x - p1.x) * (p2.x - p1.x) +
      (p2.y - p1.y) * (p2.y - p1.y));
}

namespace geometry_literals
{
   export int_point operator ""_ip(const char* ptr, std::size_t size)
   {
      int x = 0, y = 0;
      while (*ptr != ',' && *ptr != ' ') 
         x = x * 10 + (*ptr++ - '0');
      while (*ptr == ',' || *ptr == ' ') ptr++;
      while (*ptr != 0) 
         y = y * 10 + (*ptr++ - '0');
      return { x, y };
   }
}
