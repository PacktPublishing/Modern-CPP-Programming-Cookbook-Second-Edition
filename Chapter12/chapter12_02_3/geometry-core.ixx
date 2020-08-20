export module geometry.core;

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