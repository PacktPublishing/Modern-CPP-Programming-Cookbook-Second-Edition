#include <iostream>
#include <optional>

#include <cppcoro/generator.hpp>

cppcoro::generator<int> get_values() noexcept
{
   co_yield 1;
   co_yield 2;
   co_yield 3;
}

cppcoro::generator<int> iota(int start = 0, int step = 1) noexcept
{
   auto value = start;
   for (int i = 0;; ++i)
   {
      co_yield value;
      value += step;
   }
}

cppcoro::generator<std::optional<int>> iota_n(int start = 0, int step = 1, int n = std::numeric_limits<int>::max()) noexcept
{
   auto value = start;
   for (int i = 0; i < n; ++i)
   {
      co_yield value;
      value += step;
   }
}

cppcoro::generator<int> fibonacci() noexcept
{
   int a = 0, b = 1;
   while (true)
   {
      co_yield b;
      auto tmp = a;
      a = b;
      b += tmp;
   }
}

int main()
{
   std::cout << "get_values():";
   for (auto i : get_values())
   {
      std::cout << i << ' ';
   }
   std::cout << '\n';

   std::cout << "iota():";
   for (auto i : iota())
   {
      std::cout << i << ' ';
      if (i >= 10) break;
   }
   std::cout << '\n';

   std::cout << "iota_n(0,1,10):";
   for (auto i : iota_n(0, 1, 10))
   {
      if (!i.has_value()) break;
      std::cout << i.value() << ' ';
   }
   std::cout << '\n';

   std::cout << "iota(10, -2):";
   int c = 1;
   for (auto i : iota(10, -2))
   {
      std::cout << i << ' ';
      if (++c > 10) break;
   }
   std::cout << '\n';

   std::cout << "fibonacci:";
   c = 1;
   for (auto i : fibonacci())
   {
      std::cout << i << ' ';
      if (++c > 10) break;
   }
   std::cout << '\n';
}
