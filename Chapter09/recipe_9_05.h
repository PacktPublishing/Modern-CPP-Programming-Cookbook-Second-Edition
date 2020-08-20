#pragma once

namespace recipe_9_05
{
#ifdef HAS_CONSTEVAL
   consteval unsigned int factorial(unsigned int const n)
   {
      return n > 1 ? n * factorial(n - 1) : 1;
   }

   class point3d
   {
      double x_;
      double y_;
      double z_;
   public:
      consteval point3d(double const x = 0,
         double const y = 0,
         double const z = 0)
         :x_{ x }, y_{ y }, z_{ z }
      {}

      consteval double get_x() const { return x_; }
      consteval double get_y() const { return y_; }
      consteval double get_z() const { return z_; }
   };

   consteval auto addr_factorial()
   {
      return &factorial;
   }

   consteval unsigned int invoke_factorial(unsigned int const n)
   {
      return addr_factorial()(n);
   }
#endif

   void execute()
   {
#if HAS_CONSTEVAL
      {
         constexpr unsigned int f = factorial(6);
         std::cout << f << '\n';

         constexpr point3d p{ 0, 1, 2 };
         std::cout << p.get_x() << ' ' << p.get_y() << ' ' << p.get_z() << '\n';
      }

      {
         unsigned int n;
         std::cin >> n;
         //const unsigned int f2 = factorial(n); // error

         double x = 0, y = 1, z = 2;
         //constexpr point3d p2{ x, y, z };      // error
      }

      {
         using pfact = unsigned int(unsigned int);
         pfact* pf = factorial;
         //constexpr unsigned int f3 = pf(42); // error

         //constexpr auto ptr = addr_factorial();  // ERROR: cannot take the pointer
                                                 // of an immediate function
         constexpr unsigned int f2 = invoke_factorial(5); // OK
      }
#endif
   }
}