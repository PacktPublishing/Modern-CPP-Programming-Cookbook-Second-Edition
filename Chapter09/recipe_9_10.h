#pragma once

#include <string>
#include <array>
#include <compare>
#include <cassert>

namespace recipe_9_10
{
   namespace v1
   {
      class foo
      {
         int value;
      public:
         foo(int const v) :value(v) {}

         bool operator==(foo const&) const = default;
      };
   }

   namespace v2
   {
      class foo
      {
         int value;
      public:
         foo(int const v) :value(v) {}

         auto operator<=>(foo const&) const = default;
      };
   }

   namespace v3
   {
      class foo
      {
         int value;
      public:
         foo(int const v) :value(v) {}

         bool operator==(foo const& other) const
         {
            return value == other.value;
         }

         auto operator<=>(foo const& other) const
         {
            return value <=> other.value;
         }
      };
   }

   class cost_unit_t
   {
      // data members
   public:
      std::strong_ordering operator<=>(cost_unit_t const& other) const noexcept = default;
   };

   class project_t : public cost_unit_t
   {
      int         id;
      int         type;
      std::string name;
   public:
      bool operator==(project_t const& other) const noexcept
      {
         return (cost_unit_t&)(*this) == (cost_unit_t&)other &&
            name == other.name &&
            type == other.type &&
            id == other.id;
      }

      std::strong_ordering operator<=>(project_t const& other) const noexcept
      {
         // compare the base class members
         if (auto cmp = (cost_unit_t&)(*this) <=> (cost_unit_t&)other; cmp != 0) return cmp;
         // compare this class members in custom order
         if (auto cmp = name.compare(other.name); cmp != 0)
            return cmp < 0 ? std::strong_ordering::less : std::strong_ordering::greater;
         if (auto cmp = type <=> other.type; cmp != 0) return cmp;
         return id <=> other.id;
      }
   };

   struct employee_t
   {
      bool is_managed_by(employee_t const&) const { /* ... */ }
      bool is_manager_of(employee_t const&) const { /* ... */ }
      bool is_same(employee_t const&) const { /* ... */ }

      bool operator==(employee_t const& other) const
      {
         return is_same(other);
      }

      std::partial_ordering operator<=>(employee_t const& other) const noexcept
      {
         if (is_same(other))
            return std::partial_ordering::equivalent;
         if (is_managed_by(other))
            return std::partial_ordering::less;
         if (is_manager_of(other))
            return std::partial_ordering::greater;
         return std::partial_ordering::unordered;
      }
   };

   struct ipv4
   {
      explicit ipv4(unsigned char const a = 0, unsigned char const b = 0,
         unsigned char const c = 0, unsigned char const d = 0) noexcept :
         data{ a,b,c,d }
      {}

      unsigned long to_ulong() const noexcept
      {
         return
            (static_cast<unsigned long>(data[0]) << 24) |
            (static_cast<unsigned long>(data[1]) << 16) |
            (static_cast<unsigned long>(data[2]) << 8) |
            static_cast<unsigned long>(data[3]);
      }

      auto operator<=>(ipv4 const&) const noexcept = default;

      bool operator==(unsigned long const other) const noexcept
      {
         return to_ulong() == other;
      }

      std::strong_ordering operator<=>(unsigned long const other) const noexcept
      {
         return to_ulong() <=> other;
      }

   private:
      std::array<unsigned char, 4> data;
   };

   struct A { int i; };

   struct B
   {
      B(A a) : i(a.i) { }
      int i;
   };

   inline auto operator<=>(B const& lhs, B const& rhs) noexcept
   {
      return lhs.i <=> rhs.i;
   }

   void execute()
   {
      {
         v1::foo f{42};
      }

      {
         v2::foo f{42};
      }

      {
         v3::foo f1{ 42 };
         v3::foo f2{ 100 };
         if (f1 < f2) { /* do something */ }
         if (f1 == f2) { /* do something */ }
      }

      {
         ipv4 ip(127, 0, 0, 1);
         if (ip == 0x7F000001) {}
         if (ip != 0x7F000001) {}
         if (0x7F000001 == ip) {}
         if (0x7F000001 != ip) {}
         if (ip < 0x7F000001) {}
         if (0x7F000001 < ip) {}
      }

      {
         assert(A{ 2 } < A{ 1 });
      }
   }
}