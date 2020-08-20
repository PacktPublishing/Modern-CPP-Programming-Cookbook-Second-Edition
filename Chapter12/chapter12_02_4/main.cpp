import std.core;
import geometry.core;
import geometry.literals;

int main()
{
   int_point p{ 3, 4 };
   std::cout << distance(int_point_zero, p) << '\n';

   {
      using namespace geometry_literals;
      std::cout << distance("0,0"_ip, "30,40"_ip) << '\n';
   }
}