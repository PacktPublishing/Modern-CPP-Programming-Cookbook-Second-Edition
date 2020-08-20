export module geometry:literals;

import :core;
import :details;

namespace geometry_literals
{
   export int_point operator ""_ip(const char* ptr, std::size_t size)
   {
     auto [x, y]  = split(ptr, size);
     return {x, y};
   }
}
