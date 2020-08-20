#include <type_traits>
#include <iostream>
#include <string>

#include <concepts>

// ---------------basic example -------------
namespace v1
{
   template <typename T, 
             typename = typename std::enable_if_t<std::is_arithmetic_v<T>, T>>
   struct NumericalValue
   {
      T value;
   };

   template <typename T>
   NumericalValue<T> wrap(T value)
   {
      return { value };
   }

   template <typename T>
   T unwrap(NumericalValue<T> t) noexcept
   {
      return t.value;
   }
}

namespace v2
{
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

   template <class T>
   concept Real = std::is_floating_point_v<T>;

   template<Real T>
   constexpr T pi = T(3.1415926535897932385L);
}

// ------------- conjunction example ------------
namespace v3
{
   struct IComparableToInt
   {
      virtual bool CompareTo(int const o) = 0;
   };

   struct IConvertibleToInt
   {
      virtual int ConvertTo() = 0;
   };

   template <typename T>
   struct SmartNumericalValue : public IComparableToInt, IConvertibleToInt
   {
      T value;

      SmartNumericalValue(T v) :value(v) {}

      bool CompareTo(int const o) override { return static_cast<int>(value) == o; }
      int ConvertTo() override { return static_cast<int>(value); }
   };

   template <typename T>
   struct DullNumericalValue : public IConvertibleToInt
   {
      T value;

      DullNumericalValue(T v) :value(v) {}

      int ConvertTo() override { return static_cast<int>(value); }
   };

   template <class T>
   concept IntComparable = std::is_base_of_v<IComparableToInt, T>;

   template <class T>
   concept IntConvertible = std::is_base_of_v<IConvertibleToInt, T>;

   template <class T>
   concept IntComparableAndConvertible = IntComparable<T> && IntConvertible<T>;

   template <IntComparableAndConvertible T>
   void print(T o)
   {
      std::cout << o.value << '\n';
   }
}

// ------------- disjunction example ------------
namespace v4
{
   template <class T>
   concept Integral = std::is_integral_v<T>;

   template <class T>
   concept Real = std::is_floating_point_v<T>;

   template <class T>
   concept Numerical = Integral<T> || Real<T>;

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
}

namespace v5
{
   template <class T>
   concept Numerical = std::integral<T> || std::floating_point<T>;

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
}

int main()
{
   {
      using namespace v1;

      auto nv = wrap(42);
      std::cout << nv.value << '\n';   // prints 42

      auto v = unwrap(nv);
      std::cout << v << '\n';          // prints 42

      //using namespace std::string_literals;
      //auto ns = wrap("42"s);        // error
   }

   {
      using namespace v2;

      auto nv = wrap(42);
      std::cout << nv.value << '\n';   // prints 42

      auto v = unwrap(nv);
      std::cout << v << '\n';          // prints 42

      //using namespace std::string_literals;
      //auto ns = wrap("42"s);        // error

      std::cout << pi<float> << '\n';
      std::cout << pi<double> << '\n';
      //std::cout << pi<int> << '\n'; // error
   }

   {
      using namespace v3;

      auto snv = SmartNumericalValue<double>{ 42.0 };
      print(snv);                      // prints 42

      auto dnv = DullNumericalValue<short>{ 42 };
      // print(dnv);                      // error
   }

   {
      using namespace v4;
      auto nv = wrap(42);
      std::cout << nv.value << '\n';   // prints 42

      auto v = unwrap(nv);
      std::cout << v << '\n';          // prints 42

      //using namespace std::string_literals;
      //auto ns = wrap("42"s);        // error
   }

   {
      using namespace v5;

      auto nv = wrap(42);
      std::cout << nv.value << '\n';   // prints 42

      auto v = unwrap(nv);
      std::cout << v << '\n';          // prints 42

      //using namespace std::string_literals;
      //auto ns = wrap("42"s);        // error
   }
}