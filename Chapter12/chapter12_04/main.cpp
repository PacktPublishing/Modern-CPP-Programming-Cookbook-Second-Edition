#include "features.h"
#include <type_traits>
#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <concepts>

using namespace std::string_literals;

template <class T>
concept Numerical = std::is_arithmetic_v<T>;

template <Numerical T>
struct NumericalValue
{
   T value;
};

template <Numerical T>
NumericalValue<T> wrap(T value)
{
   return { value };
}

template <Numerical T>
T unwrap(NumericalValue<T> t) noexcept
{
   return t.value;
}

#ifdef HAS_REQUIRES_EXPR
namespace v1
{
   template <typename T>
   concept Addable = requires (T a, T b) { a + b; };

   template <Addable T>
   T add(T a, T b)
   {
      return a + b;
   }

   template <typename T>
   concept Wrapable = requires(T x) { wrap(x); };

   template <Wrapable T>
   void do_wrap(T x)
   {
      [[maybe_unused]] auto v = wrap(x);
   }

   template <typename T>
   concept Container = requires(T x)
   {
      typename T::value_type;
      typename T::iterator;
      begin(x);
      end(x);
   };

   template <Container T>
   void pass_container(T const& c)
   {
      for (auto const& x : c)
         std::cout << x << '\n';
   }

   template <typename T>
   concept NumericalWrapable =
   requires(T x)
   {
      {wrap(x)}->std::same_as<NumericalValue<T>>;
   };

   template <NumericalWrapable T>
   void do_wrap_numerical(T x)
   {
      [[maybe_unused]] auto v = wrap(x);
   }

   template <typename T>
   class any_wrapper
   {
   public:
      T value;
   };

   any_wrapper<std::string> wrap(std::string s)
   {
      return any_wrapper<std::string>{s};
   }
}

namespace v2
{
   template <typename T>
   concept Addable = requires (T a, T b) { a + b; };

   template <typename T> requires Addable<T>
   T add(T a, T b)
   {
      return a + b;
   }
}

namespace v3
{
   template <typename T>
   concept Addable = requires (T a, T b) { a + b; };

   template <typename T>
   T add(T a, T b) requires Addable<T>
   {
      return a + b;
   }
}

namespace v4
{
   template <typename T>
   T add(T a, T b) requires requires (T a, T b) { a + b; }
   {
      return a + b;
   }
}
#endif

int main()
{
#ifdef HAS_REQUIRES_EXPR
   {
      using namespace v1;
      {
         add(1, 2);
         add("1"s, "2"s);

         //NumericalValue<int> a{1};
         //NumericalValue<int> b{2} ;
         //add(a, b); // error: no matching function for call to 'add'
                    // 'NumericalValue<int>' does not satisfy 'Addable'
      }

      {
         do_wrap(42);
         do_wrap(42.0);
         //do_wrap("42"s); // error
      }

      {
         std::vector<int> v{ 1, 2, 3 };
         std::array<int, 3> a{ 1, 2, 3 };
         //int arr[] {1,2,3};

         pass_container(v);
         pass_container(a);
         //pass_container(arr); // error: 'int [3]' does not satisfy 'Container'
      }

      {
         do_wrap_numerical(42);
         do_wrap_numerical(42.0);
         //do_wrap_numerical("42"s); // error
      }

   }

   {
      using namespace v2;

      add(1, 2);
      add("1"s, "2"s);

      //NumericalValue<int> a{1};
      //NumericalValue<int> b{2} ;
      //add(a, b); // error: no matching function for call to 'add'
   }

   {
      using namespace v3;

      add(1, 2);
      add("1"s, "2"s);

      //NumericalValue<int> a{1};
      //NumericalValue<int> b{2} ;
      //add(a, b); // error: no matching function for call to 'add'

   }

   {
      using namespace v4;

      add(1, 2);
      add("1"s, "2"s);

      //NumericalValue<int> a{1};
      //NumericalValue<int> b{2} ;
      //add(a, b); // error: no matching function for call to 'add'

   }
#endif
}