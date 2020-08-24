#pragma once

#include <cassert>
#include <string>
#include <memory>
#include <algorithm>
#include <iostream>

namespace recipe_5_10
{
   using namespace std::string_literals;

   struct Task
   {
      int priority;
      std::string name;
   };

   struct Tag
   {
      int id;
      std::string name;

      Tag(int const id = 0, std::string const& name = ""s) :
         id(id), name(name)
      {}
   };

   template <typename Type, size_t const SIZE>
   class dummy_array
   {
      Type data[SIZE] = {};

   public:
      Type& operator[](size_t const index)
      {
         if (index < SIZE) return data[index];
         throw std::out_of_range("index out of range");
      }

      Type const& operator[](size_t const index) const
      {
         if (index < SIZE) return data[index];
         throw std::out_of_range("index out of range");
      }

      size_t size() const { return SIZE; }

      template <typename T, size_t const Size>
      class dummy_array_iterator
      {
      public:
         typedef dummy_array_iterator              self_type;
         typedef T                                 value_type;
         typedef T& reference;
         typedef T* pointer;
         typedef std::random_access_iterator_tag   iterator_category;
         typedef ptrdiff_t                         difference_type;

      private:
         pointer  ptr = nullptr;
         size_t   index = 0;

         bool compatible(self_type const& other) const
         {
            return ptr == other.ptr;
         }

      public:
         explicit dummy_array_iterator(pointer ptr, size_t const index) :
            ptr(ptr), index(index)
         {
         }

         // --- common to all iterators ---
         // copy-constructible, copy-assignable and destructible
         dummy_array_iterator(dummy_array_iterator const& o) = default;
         dummy_array_iterator& operator=(dummy_array_iterator const& o) = default;
         ~dummy_array_iterator() = default;

         // can be prefix- and postfix- incremented
         self_type& operator++ ()
         {
            if (index >= Size)
               throw std::out_of_range("Iterator cannot be incremented past the end of range.");
            ++index;
            return *this;
         }

         self_type operator++ (int)
         {
            self_type tmp = *this;
            ++* this;
            return tmp;
         }
         // --- common to all iterators ---

         // --- input iterator ---
         // supports equality/inequality comparisons
         bool operator== (self_type const& other) const
         {
            assert(compatible(other));
            return index == other.index;
         }

         bool operator!= (self_type const& other) const
         {
            return !(*this == other);
         }

         // can be dereferenced as an rvalue
         reference operator* () const
         {
            if (ptr == nullptr)
               throw std::bad_function_call();
            return *(ptr + index);
         }

         reference operator-> () const
         {
            if (ptr == nullptr)
               throw std::bad_function_call();
            return *(ptr + index);
         }

         // --- input iterator ---

         // --- output iterator ---
         // can be dereferenced as an lvalue
         // --- output iterator ---

         // --- forward iterator ---
         // default-constructible
         dummy_array_iterator() = default;

         // multi-pass: neither dereferencing nor incrementing affects dereferenceability
         // --- forward iterator ---

         // --- bidirectional iterator ---
         // can be decremented
         self_type& operator--()
         {
            if (index <= 0)
               throw std::out_of_range("Iterator cannot be decremented past the end of range.");
            --index;
            return *this;
         }

         self_type operator--(int)
         {
            self_type tmp = *this;
            --* this;
            return tmp;
         }
         // --- bidirectional iterator ---

         // --- random access iterator ---
         // supports arithmetic operators + and -
         self_type operator+(difference_type offset) const
         {
            self_type tmp = *this;
            return tmp += offset;
         }

         self_type operator-(difference_type offset) const
         {
            self_type tmp = *this;
            return tmp -= offset;
         }

         difference_type operator-(self_type const& other) const
         {
            assert(compatible(other));
            return (index - other.index);
         }

         // supports inequality comparisons (<, >, <= and >=) between iterators
         bool operator<(self_type const& other) const
         {
            assert(compatible(other));
            return index < other.index;
         }

         bool operator>(self_type const& other) const
         {
            return other < *this;
         }

         bool operator<=(self_type const& other) const
         {
            return !(other < *this);
         }

         bool operator>=(self_type const& other) const
         {
            return !(*this < other);
         }

         // supports compound assignment operations += and -=
         self_type& operator+=(difference_type const offset)
         {
            if (index + offset < 0 || index + offset > Size)
               throw std::out_of_range("Iterator cannot be incremented past the end of range.");

            index += offset;
            return *this;
         }

         self_type& operator-=(difference_type const offset)
         {
            return *this += -offset;
         }

         // supports offset dereference operator ([])
         value_type& operator[](difference_type const offset)
         {
            return (*(*this + offset));
         }

         value_type const& operator[](difference_type const offset) const
         {
            return (*(*this + offset));
         }
         // --- random access iterator ---
      };

      typedef dummy_array_iterator<Type, SIZE>        iterator;
      typedef dummy_array_iterator<Type const, SIZE>  constant_iterator;

   public:
      iterator begin()
      {
         return iterator(data, 0);
      }

      iterator end()
      {
         return iterator(data, SIZE);
      }

      constant_iterator begin() const
      {
         return constant_iterator(data, 0);
      }

      constant_iterator end() const
      {
         return constant_iterator(data, SIZE);
      }
   };

   void execute()
   {
      {
         dummy_array<int, 5> a;
         a[0] = 1;
         a[1] = 2;
         a[2] = 3;
         a[3] = 4;
         a[4] = 5;
         dummy_array<int, 5> b;

         dummy_array<int, 5>::iterator i1 = a.begin();
         dummy_array<int, 5>::iterator i2 = a.begin();
         dummy_array<int, 5>::iterator i3 = a.begin();
         dummy_array<int, 5>::iterator i4 = a.end();

         dummy_array<int, 5>::iterator y1 = b.begin();

         // copy-constructible, copy-assignable and destructible
         auto ci1(i1);
         ci1 = i3;

         // incrementable
         ++ci1;
         ci1++;

         // equality/inequality comparison
         [[maybe_unused]] auto e1 = i1 == i2;
         [[maybe_unused]] auto e2 = i1 == i3;
         //auto e3 = i1 == y1;

         // dereferenced as rvalue
         if (*i1 > 0) {}

         // dereferenced as lvalue
         *i1 = 11;
         *i1++ = 111;

         // default constructible
         dummy_array<int, 5>::iterator i0;
         dummy_array<int, 5>::iterator();

         // multi-pass
         {
            i2 = i1;
            *i1++;
            *i2;
         }

         // decrementable
         --i4;
         i4--;
         *i4--;

         // arithmetic increment and decrement
         auto x1 = i1 + 2;
         //auto x2 = 1 + i1;
         auto x3 = i4 - 1;
         [[maybe_unused]] auto d = x1 - x3;

         // logical comparison
         [[maybe_unused]] auto ls = i1 < i4;
         [[maybe_unused]] auto gt = i1 > i4;
         [[maybe_unused]] auto le = i1 <= i4;
         [[maybe_unused]] auto ge = i1 >= i4;

         // compound assignment
         i1 += 2;
         i1 += -2;
         i1 -= -2;
         i1 -= 2;

         // offset dereference operator
         [[maybe_unused]] auto e = i1[2];
      }

      {
         dummy_array<int, 5> a;
         a[0] = 10;
         a[1] = 20;
         a[2] = 30;
         a[3] = 40;
         a[4] = 50;

         std::transform(a.begin(), a.end(), a.begin(), [](int const e) {return e * 2; });

         for (auto&& e : a) std::cout << e << '\n';
      }

      {
         dummy_array<int, 5> a;
         a[0] = 10;
         a[1] = 20;
         a[2] = 30;
         a[3] = 40;
         a[4] = 50;

         for (auto&& e : a) std::cout << e << '\n';

         auto lp = [](dummy_array<int, 5> const& ca)
         {
            for (auto const& e : ca)
               std::cout << e << '\n';
         };

         lp(a);
      }

      {
         dummy_array<Task, 5> a;
         a[0] = Task{ 10, "Task 1" };
         a[1] = Task{ 20, "Task 2" };
         a[2] = Task{ 30, "Task 3" };
         a[3] = Task{ 40, "Task 4" };
         a[4] = Task{ 50, "Task 5" };

         for (auto&& e : a)
            std::cout << e.priority << " " << e.name << '\n';

         auto p0 = &a[0];
         std::cout << p0->priority << " " << p0->name << '\n';
      }

      {
         dummy_array<std::unique_ptr<Tag>, 5> a;
         a[0] = std::make_unique<Tag>(1, "Tag 1");
         a[1] = std::make_unique<Tag>(2, "Tag 2");
         a[2] = std::make_unique<Tag>(3, "Tag 3");
         a[3] = std::make_unique<Tag>(4, "Tag 4");
         a[4] = std::make_unique<Tag>(5, "Tag 5");

         for (auto it = a.begin(); it != a.end(); ++it)
            std::cout << it->id << " " << it->name << '\n';

         auto p0 = a[0].get();
         std::cout << p0->id << " " << p0->name << '\n';
      }

      {
         dummy_array<int, 5> a;
         a[0] = 10;
         a[1] = 20;
         a[2] = 30;
         a[3] = 40;
         a[4] = 50;

         auto lp = [](dummy_array<int, 5> const& arr)
         {
            for (size_t i = 0; i < arr.size(); ++i)
            {
               std::cout << arr[i] << '\n';
            }
         };

         lp(a);
      }
   }
}
