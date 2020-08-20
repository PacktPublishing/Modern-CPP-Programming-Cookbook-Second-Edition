#pragma once

namespace recipe_3_06
{  
   template <typename... Ts>
   auto add(Ts... args)
   {
      return (... + args);
   }

   template <typename... Ts>
   auto addr(Ts... args)
   {
      return (args + ...);
   }

   template <typename... Ts>
   auto all_of(Ts... args)
   {
      return (... && args);
   }

   template <typename... Ts>
   auto any_of(Ts... args)
   {
      return (... || args);
   }
   
   template <typename T>
   struct wrapper_min
   {
      T const & value;
   };

   template <typename T>
   constexpr auto operator<(wrapper_min<T> const & lhs, wrapper_min<T> const & rhs)
   {
      return wrapper_min<T> {lhs.value < rhs.value ? lhs.value : rhs.value};
   }

   template <typename... Ts>
   constexpr auto min(Ts&&... args)
   {
      return (wrapper_min<Ts>{args} < ...).value;
   }

   void execute()
   {
      std::cout << min(10, 2, 3, 4, 5) << '\n';

      std::cout << add(1) << '\n';
      std::cout << add(1, 2, 3, 4, 5) << '\n';
      std::cout << addr(1, 2, 3, 4, 5) << '\n';

      std::cout << all_of(true, true, true) << '\n';
      std::cout << all_of(false, false, false) << '\n';
      std::cout << all_of(true, false, true) << '\n';

      std::cout << any_of(true, true, true) << '\n';
      std::cout << any_of(false, false, false) << '\n';
      std::cout << any_of(true, false, true) << '\n';
   }
}