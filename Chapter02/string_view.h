// -*- C++ -*-
//===------------------------ string_view ---------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef _LIBCPP_LFTS_STRING_VIEW
#define _LIBCPP_LFTS_STRING_VIEW

#include <string>
#include <algorithm>
#include <iterator>
#include <ostream>
#include <stdexcept>
#include <iomanip>
#include <assert.h>

namespace std {
    inline 
       void __throw_out_of_range(const char*__msg)
   {
      throw out_of_range(__msg);
   }

    // __str_find_first_not_of
    template<class _CharT, class _SizeT, class _Traits, _SizeT __npos>
    inline _SizeT
       __str_find_first_not_of(const _CharT *__p, _SizeT __sz,
          const _CharT* __s, _SizeT __pos, _SizeT __n) _NOEXCEPT
    {
       if (__pos < __sz)
       {
          const _CharT* __pe = __p + __sz;
          for (const _CharT* __ps = __p + __pos; __ps != __pe; ++__ps)
             if (_Traits::find(__s, __n, *__ps) == 0)
                return static_cast<_SizeT>(__ps - __p);
       }
       return __npos;
    }


    template<class _CharT, class _SizeT, class _Traits, _SizeT __npos>
    inline _SizeT
       __str_find_first_not_of(const _CharT *__p, _SizeT __sz,
          _CharT __c, _SizeT __pos) _NOEXCEPT
    {
       if (__pos < __sz)
       {
          const _CharT* __pe = __p + __sz;
          for (const _CharT* __ps = __p + __pos; __ps != __pe; ++__ps)
             if (!_Traits::eq(*__ps, __c))
                return static_cast<_SizeT>(__ps - __p);
       }
       return __npos;
    }


    // __str_find_last_not_of
    template<class _CharT, class _SizeT, class _Traits, _SizeT __npos>
    inline _SizeT 
       __str_find_last_not_of(const _CharT *__p, _SizeT __sz,
          const _CharT* __s, _SizeT __pos, _SizeT __n) _NOEXCEPT
    {
       if (__pos < __sz)
          ++__pos;
       else
          __pos = __sz;
       for (const _CharT* __ps = __p + __pos; __ps != __p;)
          if (_Traits::find(__s, __n, *--__ps) == 0)
             return static_cast<_SizeT>(__ps - __p);
       return __npos;
    }


    template<class _CharT, class _SizeT, class _Traits, _SizeT __npos>
    inline _SizeT
       __str_find_last_not_of(const _CharT *__p, _SizeT __sz,
          _CharT __c, _SizeT __pos) _NOEXCEPT
    {
       if (__pos < __sz)
          ++__pos;
       else
          __pos = __sz;
       for (const _CharT* __ps = __p + __pos; __ps != __p;)
          if (!_Traits::eq(*--__ps, __c))
             return static_cast<_SizeT>(__ps - __p);
       return __npos;
    }

   template<class _CharT, class _SizeT, class _Traits, _SizeT __npos>
   inline _SizeT
      __str_rfind(const _CharT *__p, _SizeT __sz,
         _CharT __c, _SizeT __pos) _NOEXCEPT
   {
      if (__sz < 1)
         return __npos;
      if (__pos < __sz)
         ++__pos;
      else
         __pos = __sz;
      for (const _CharT* __ps = __p + __pos; __ps != __p;)
      {
         if (_Traits::eq(*--__ps, __c))
            return static_cast<_SizeT>(__ps - __p);
      }
      return __npos;
   }

   template<class _CharT, class _SizeT, class _Traits, _SizeT __npos>
   inline _SizeT
      __str_rfind(const _CharT *__p, _SizeT __sz,
         const _CharT* __s, _SizeT __pos, _SizeT __n) _NOEXCEPT
   {
      __pos = _VSTD::min(__pos, __sz);
      if (__n < __sz - __pos)
         __pos += __n;
      else
         __pos = __sz;
      const _CharT* __r = _VSTD::__find_end(
         __p, __p + __pos, __s, __s + __n, _Traits::eq,
         random_access_iterator_tag(), random_access_iterator_tag());
      if (__n > 0 && __r == __p + __pos)
         return __npos;
      return static_cast<_SizeT>(__r - __p);
   }

   namespace experimental {
      inline namespace fundamentals_v1 {


         template<class _CharT, class _Traits = std::char_traits<_CharT> >
         class basic_string_view {
         public:
            // types
            typedef _Traits                                    traits_type;
            typedef _CharT                                     value_type;
            typedef const _CharT*                              pointer;
            typedef const _CharT*                              const_pointer;
            typedef const _CharT&                              reference;
            typedef const _CharT&                              const_reference;
            typedef const_pointer                              const_iterator; // See [string.view.iterators]
            typedef const_iterator                             iterator;
            typedef std::reverse_iterator<const_iterator>    const_reverse_iterator;
            typedef const_reverse_iterator                     reverse_iterator;
            typedef size_t                                     size_type;
            typedef ptrdiff_t                                  difference_type;
            static constexpr const size_type npos = -1; // size_type(-1);

                                                                // [string.view.cons], construct/copy
            constexpr inline
               basic_string_view() _NOEXCEPT : __data(nullptr), __size(0) {}

            constexpr inline
               basic_string_view(const basic_string_view&) _NOEXCEPT = default;

            inline
               basic_string_view& operator=(const basic_string_view&) _NOEXCEPT = default;

            template<class _Allocator>
            inline
               basic_string_view(const basic_string<_CharT, _Traits, _Allocator>& __str) _NOEXCEPT
               : __data(__str.data()), __size(__str.size()) {}

            constexpr inline
               basic_string_view(const _CharT* __s, size_type __len)
               : __data(__s), __size(__len)
            {
               //             _LIBCPP_ASSERT(__len == 0 || __s != nullptr, "string_view::string_view(_CharT *, size_t): received nullptr");
            }

            constexpr inline
               basic_string_view(const _CharT* __s)
               : __data(__s), __size(_Traits::length(__s)) {}

            // [string.view.iterators], iterators
            constexpr inline
               const_iterator begin()  const _NOEXCEPT { return cbegin(); }

            constexpr inline
               const_iterator end()    const _NOEXCEPT { return cend(); }

            constexpr inline
               const_iterator cbegin() const _NOEXCEPT { return __data; }

            constexpr inline
               const_iterator cend()   const _NOEXCEPT { return __data + __size; }

            inline
               const_reverse_iterator rbegin()   const _NOEXCEPT { return const_reverse_iterator(cend()); }

            inline
               const_reverse_iterator rend()     const _NOEXCEPT { return const_reverse_iterator(cbegin()); }

            inline
               const_reverse_iterator crbegin()  const _NOEXCEPT { return const_reverse_iterator(cend()); }

            inline
               const_reverse_iterator crend()    const _NOEXCEPT { return const_reverse_iterator(cbegin()); }

            // [string.view.capacity], capacity
            constexpr inline
               size_type size()     const _NOEXCEPT { return __size; }

            constexpr inline
               size_type length()   const _NOEXCEPT { return __size; }

            constexpr inline
               size_type max_size() const _NOEXCEPT { return std::numeric_limits<size_type>::max(); }

            constexpr bool inline
               empty()         const _NOEXCEPT { return __size == 0; }

            // [string.view.access], element access
            constexpr inline
               const_reference operator[](size_type __pos) const { return __data[__pos]; }

            constexpr inline
               const_reference at(size_type __pos) const
            {
               return __pos >= size()
                  ? (__throw_out_of_range("string_view::at"), __data[0])
                  : __data[__pos];
            }

            constexpr inline
               const_reference front() const
            {
               return _LIBCPP_ASSERT(!empty(), "string_view::front(): string is empty"), __data[0];
            }

            constexpr inline
               const_reference back() const
            {
               return _LIBCPP_ASSERT(!empty(), "string_view::back(): string is empty"), __data[__size - 1];
            }

            constexpr inline
               const_pointer data() const _NOEXCEPT { return __data; }

            // [string.view.modifiers], modifiers:
            inline
               void clear() _NOEXCEPT
            {
               __data = nullptr;
               __size = 0;
            }

            inline
               void remove_prefix(size_type __n) _NOEXCEPT
            {
               __data += __n;
               __size -= __n;
            }

            inline
               void remove_suffix(size_type __n) _NOEXCEPT
            {
               __size -= __n;
            }

            inline
               void swap(basic_string_view& __other) _NOEXCEPT
            {
               const value_type *__p = __data;
               __data = __other.__data;
               __other.__data = __p;

               size_type __sz = __size;
               __size = __other.__size;
               __other.__size = __sz;
               //             std::swap( __data, __other.__data );
               //             std::swap( __size, __other.__size );
            }

            // [string.view.ops], string operations:
            template<class _Allocator>
            inline
               explicit operator basic_string<_CharT, _Traits, _Allocator>() const
            {
               return basic_string<_CharT, _Traits, _Allocator>(begin(), end());
            }

            template<class _Allocator = allocator<_CharT> >
            inline
               basic_string<_CharT, _Traits, _Allocator>
               to_string(const _Allocator& __a = _Allocator()) const
            {
               return basic_string<_CharT, _Traits, _Allocator>(begin(), end(), __a);
            }

            size_type copy(_CharT* __s, size_type __n, size_type __pos = 0) const
            {
               if (__pos > size())
                  __throw_out_of_range("string_view::copy");
               size_type __rlen = std::min(__n, size() - __pos);
               std::copy_n(begin() + __pos, __rlen, __s);
               return __rlen;
            }

            constexpr
               basic_string_view substr(size_type __pos = 0, size_type __n = npos) const
            {
               //             if (__pos > size())
               //                 __throw_out_of_range("string_view::substr");
               //             size_type __rlen = std::min( __n, size() - __pos );
               //             return basic_string_view(data() + __pos, __rlen);
               return __pos > size()
                  ? (__throw_out_of_range("string_view::substr"), basic_string_view())
                  : basic_string_view(data() + __pos, std::min(__n, size() - __pos));
            }

            constexpr int compare(basic_string_view __sv) const _NOEXCEPT
            {
               size_type __rlen = std::min(size(), __sv.size());
               int __retval = _Traits::compare(data(), __sv.data(), __rlen);
               if (__retval == 0) // first __rlen chars matched
                  __retval = size() == __sv.size() ? 0 : (size() < __sv.size() ? -1 : 1);
               return __retval;
            }

            constexpr inline
               int compare(size_type __pos1, size_type __n1, basic_string_view __sv) const
            {
               return substr(__pos1, __n1).compare(__sv);
            }

            constexpr inline
               int compare(size_type __pos1, size_type __n1,
                  basic_string_view _sv, size_type __pos2, size_type __n2) const
            {
               return substr(__pos1, __n1).compare(_sv.substr(__pos2, __n2));
            }

            constexpr inline
               int compare(const _CharT* __s) const
            {
               return compare(basic_string_view(__s));
            }

            constexpr inline
               int compare(size_type __pos1, size_type __n1, const _CharT* __s) const
            {
               return substr(__pos1, __n1).compare(basic_string_view(__s));
            }

            constexpr inline
               int compare(size_type __pos1, size_type __n1, const _CharT* __s, size_type __n2) const
            {
               return substr(__pos1, __n1).compare(basic_string_view(__s, __n2));
            }

            // find
            constexpr inline
               size_type find(basic_string_view __s, size_type __pos = 0) const _NOEXCEPT
            {
               _LIBCPP_ASSERT(__s.size() == 0 || __s.data() != nullptr, "string_view::find(): received nullptr");
               return std::__str_find<value_type, size_type, traits_type, npos>
                  (data(), size(), __s.data(), __pos, __s.size());
            }

            constexpr inline
               size_type find(_CharT __c, size_type __pos = 0) const _NOEXCEPT
            {
               return std::__str_find<value_type, size_type, traits_type, npos>
                  (data(), size(), __c, __pos);
            }

            constexpr inline
               size_type find(const _CharT* __s, size_type __pos, size_type __n) const
            {
               _LIBCPP_ASSERT(__n == 0 || __s != nullptr, "string_view::find(): received nullptr");
               return std::__str_find<value_type, size_type, traits_type, npos>
                  (data(), size(), __s, __pos, __n);
            }

            constexpr inline
               size_type find(const _CharT* __s, size_type __pos = 0) const
            {
               _LIBCPP_ASSERT(__s != nullptr, "string_view::find(): received nullptr");
               return std::__str_find<value_type, size_type, traits_type, npos>
                  (data(), size(), __s, __pos, traits_type::length(__s));
            }

            // rfind
            constexpr inline
               size_type rfind(basic_string_view __s, size_type __pos = npos) const _NOEXCEPT
            {
               _LIBCPP_ASSERT(__s.size() == 0 || __s.data() != nullptr, "string_view::find(): received nullptr");
               return std::__str_rfind<value_type, size_type, traits_type, npos>
                  (data(), size(), __s.data(), __pos, __s.size());
            }

            constexpr inline
               size_type rfind(_CharT __c, size_type __pos = npos) const _NOEXCEPT
            {
               return std::__str_rfind<value_type, size_type, traits_type, npos>
                  (data(), size(), __c, __pos);
            }

            constexpr inline
               size_type rfind(const _CharT* __s, size_type __pos, size_type __n) const
            {
               _LIBCPP_ASSERT(__n == 0 || __s != nullptr, "string_view::rfind(): received nullptr");
               return std::__str_rfind<value_type, size_type, traits_type, npos>
                  (data(), size(), __s, __pos, __n);
            }

            constexpr inline
               size_type rfind(const _CharT* __s, size_type __pos = npos) const
            {
               _LIBCPP_ASSERT(__s != nullptr, "string_view::rfind(): received nullptr");
               return std::__str_rfind<value_type, size_type, traits_type, npos>
                  (data(), size(), __s, __pos, traits_type::length(__s));
            }

            // find_first_of
            constexpr inline
               size_type find_first_of(basic_string_view __s, size_type __pos = 0) const _NOEXCEPT
            {
               _LIBCPP_ASSERT(__s.size() == 0 || __s.data() != nullptr, "string_view::find_first_of(): received nullptr");
               return std::__str_find_first_of<value_type, size_type, traits_type, npos>
                  (data(), size(), __s.data(), __pos, __s.size());
            }

            constexpr inline
               size_type find_first_of(_CharT __c, size_type __pos = 0) const _NOEXCEPT
            {
               return find(__c, __pos);
            }

            constexpr inline
               size_type find_first_of(const _CharT* __s, size_type __pos, size_type __n) const
            {
               _LIBCPP_ASSERT(__n == 0 || __s != nullptr, "string_view::find_first_of(): received nullptr");
               return std::__str_find_first_of<value_type, size_type, traits_type, npos>
                  (data(), size(), __s, __pos, __n);
            }

            constexpr inline
               size_type find_first_of(const _CharT* __s, size_type __pos = 0) const
            {
               _LIBCPP_ASSERT(__s != nullptr, "string_view::find_first_of(): received nullptr");
               return std::__str_find_first_of<value_type, size_type, traits_type, npos>
                  (data(), size(), __s, __pos, traits_type::length(__s));
            }

            // find_last_of
            constexpr inline
               size_type find_last_of(basic_string_view __s, size_type __pos = npos) const _NOEXCEPT
            {
               _LIBCPP_ASSERT(__s.size() == 0 || __s.data() != nullptr, "string_view::find_last_of(): received nullptr");
               return std::__str_find_last_of<value_type, size_type, traits_type, npos>
                  (data(), size(), __s.data(), __pos, __s.size());
            }

            constexpr inline
               size_type find_last_of(_CharT __c, size_type __pos = npos) const _NOEXCEPT
            {
               return rfind(__c, __pos);
            }

            constexpr inline
               size_type find_last_of(const _CharT* __s, size_type __pos, size_type __n) const
            {
               _LIBCPP_ASSERT(__n == 0 || __s != nullptr, "string_view::find_last_of(): received nullptr");
               return std::__str_find_last_of<value_type, size_type, traits_type, npos>
                  (data(), size(), __s, __pos, __n);
            }

            constexpr inline
               size_type find_last_of(const _CharT* __s, size_type __pos = npos) const
            {
               _LIBCPP_ASSERT(__s != nullptr, "string_view::find_last_of(): received nullptr");
               return std::__str_find_last_of<value_type, size_type, traits_type, npos>
                  (data(), size(), __s, __pos, traits_type::length(__s));
            }

            // find_first_not_of
            constexpr inline
               size_type find_first_not_of(basic_string_view __s, size_type __pos = 0) const _NOEXCEPT
            {
               _LIBCPP_ASSERT(__s.size() == 0 || __s.data() != nullptr, "string_view::find_first_not_of(): received nullptr");
               return std::__str_find_first_not_of<value_type, size_type, traits_type, npos>
                  (data(), size(), __s.data(), __pos, __s.size());
            }

            constexpr inline
               size_type find_first_not_of(_CharT __c, size_type __pos = 0) const _NOEXCEPT
            {
               return std::__str_find_first_not_of<value_type, size_type, traits_type, npos>
                  (data(), size(), __c, __pos);
            }

            constexpr inline
               size_type find_first_not_of(const _CharT* __s, size_type __pos, size_type __n) const
            {
               _LIBCPP_ASSERT(__n == 0 || __s != nullptr, "string_view::find_first_not_of(): received nullptr");
               return std::__str_find_first_not_of<value_type, size_type, traits_type, npos>
                  (data(), size(), __s, __pos, __n);
            }

            constexpr inline
               size_type find_first_not_of(const _CharT* __s, size_type __pos = 0) const
            {
               return std::__str_find_first_not_of<value_type, size_type, traits_type, npos>
                  (data(), size(), __s, __pos, traits_type::length(__s));
            }

            // find_last_not_of
            constexpr inline
               size_type find_last_not_of(basic_string_view __s, size_type __pos = npos) const _NOEXCEPT
            {
               _LIBCPP_ASSERT(__s.size() == 0 || __s.data() != nullptr, "string_view::find_last_not_of(): received nullptr");
               return std::__str_find_last_not_of<value_type, size_type, traits_type, npos>
                  (data(), size(), __s.data(), __pos, __s.size());
            }

            constexpr inline
               size_type find_last_not_of(_CharT __c, size_type __pos = npos) const _NOEXCEPT
            {
               return std::__str_find_last_not_of<value_type, size_type, traits_type, npos>
                  (data(), size(), __c, __pos);
            }

            constexpr inline
               size_type find_last_not_of(const _CharT* __s, size_type __pos, size_type __n) const
            {
               _LIBCPP_ASSERT(__n == 0 || __s != nullptr, "string_view::find_last_not_of(): received nullptr");
               return std::__str_find_last_not_of<value_type, size_type, traits_type, npos>
                  (data(), size(), __s, __pos, __n);
            }

            constexpr inline
               size_type find_last_not_of(const _CharT* __s, size_type __pos = npos) const
            {
               return std::__str_find_last_not_of<value_type, size_type, traits_type, npos>
                  (data(), size(), __s, __pos, traits_type::length(__s));
            }

         private:
            const   value_type* __data;
            size_type           __size;
         };


         // [string.view.comparison]
         // operator ==
         template<class _CharT, class _Traits>
         constexpr inline
            bool operator==(basic_string_view<_CharT, _Traits> __lhs,
               basic_string_view<_CharT, _Traits> __rhs) _NOEXCEPT
         {
            if (__lhs.size() != __rhs.size()) return false;
            return __lhs.compare(__rhs) == 0;
         }

         template<class _CharT, class _Traits>
         constexpr inline
            bool operator==(basic_string_view<_CharT, _Traits> __lhs,
               typename std::common_type<basic_string_view<_CharT, _Traits> >::type __rhs) _NOEXCEPT
         {
            if (__lhs.size() != __rhs.size()) return false;
            return __lhs.compare(__rhs) == 0;
         }

         template<class _CharT, class _Traits>
         constexpr inline
            bool operator==(typename std::common_type<basic_string_view<_CharT, _Traits> >::type __lhs,
               basic_string_view<_CharT, _Traits> __rhs) _NOEXCEPT
         {
            if (__lhs.size() != __rhs.size()) return false;
            return __lhs.compare(__rhs) == 0;
         }


         // operator !=
         template<class _CharT, class _Traits>
         constexpr inline
            bool operator!=(basic_string_view<_CharT, _Traits> __lhs, basic_string_view<_CharT, _Traits> __rhs) _NOEXCEPT
         {
            if (__lhs.size() != __rhs.size())
               return true;
            return __lhs.compare(__rhs) != 0;
         }

         template<class _CharT, class _Traits>
         constexpr inline
            bool operator!=(basic_string_view<_CharT, _Traits> __lhs,
               typename std::common_type<basic_string_view<_CharT, _Traits> >::type __rhs) _NOEXCEPT
         {
            if (__lhs.size() != __rhs.size())
               return true;
            return __lhs.compare(__rhs) != 0;
         }

         template<class _CharT, class _Traits>
         constexpr inline
            bool operator!=(typename std::common_type<basic_string_view<_CharT, _Traits> >::type __lhs,
               basic_string_view<_CharT, _Traits> __rhs) _NOEXCEPT
         {
            if (__lhs.size() != __rhs.size())
               return true;
            return __lhs.compare(__rhs) != 0;
         }


         // operator <
         template<class _CharT, class _Traits>
         constexpr inline
            bool operator<(basic_string_view<_CharT, _Traits> __lhs, basic_string_view<_CharT, _Traits> __rhs) _NOEXCEPT
         {
            return __lhs.compare(__rhs) < 0;
         }

         template<class _CharT, class _Traits>
         constexpr inline
            bool operator<(basic_string_view<_CharT, _Traits> __lhs,
               typename std::common_type<basic_string_view<_CharT, _Traits> >::type __rhs) _NOEXCEPT
         {
            return __lhs.compare(__rhs) < 0;
         }

         template<class _CharT, class _Traits>
         constexpr inline
            bool operator<(typename std::common_type<basic_string_view<_CharT, _Traits> >::type __lhs,
               basic_string_view<_CharT, _Traits> __rhs) _NOEXCEPT
         {
            return __lhs.compare(__rhs) < 0;
         }


         // operator >
         template<class _CharT, class _Traits>
         constexpr inline
            bool operator> (basic_string_view<_CharT, _Traits> __lhs, basic_string_view<_CharT, _Traits> __rhs) _NOEXCEPT
         {
            return __lhs.compare(__rhs) > 0;
         }

         template<class _CharT, class _Traits>
         constexpr inline
            bool operator>(basic_string_view<_CharT, _Traits> __lhs,
               typename std::common_type<basic_string_view<_CharT, _Traits> >::type __rhs) _NOEXCEPT
         {
            return __lhs.compare(__rhs) > 0;
         }

         template<class _CharT, class _Traits>
         constexpr inline
            bool operator>(typename std::common_type<basic_string_view<_CharT, _Traits> >::type __lhs,
               basic_string_view<_CharT, _Traits> __rhs) _NOEXCEPT
         {
            return __lhs.compare(__rhs) > 0;
         }


         // operator <=
         template<class _CharT, class _Traits>
         constexpr inline
            bool operator<=(basic_string_view<_CharT, _Traits> __lhs, basic_string_view<_CharT, _Traits> __rhs) _NOEXCEPT
         {
            return __lhs.compare(__rhs) <= 0;
         }

         template<class _CharT, class _Traits>
         constexpr inline
            bool operator<=(basic_string_view<_CharT, _Traits> __lhs,
               typename std::common_type<basic_string_view<_CharT, _Traits> >::type __rhs) _NOEXCEPT
         {
            return __lhs.compare(__rhs) <= 0;
         }

         template<class _CharT, class _Traits>
         constexpr inline
            bool operator<=(typename std::common_type<basic_string_view<_CharT, _Traits> >::type __lhs,
               basic_string_view<_CharT, _Traits> __rhs) _NOEXCEPT
         {
            return __lhs.compare(__rhs) <= 0;
         }


         // operator >=
         template<class _CharT, class _Traits>
         constexpr inline
            bool operator>=(basic_string_view<_CharT, _Traits> __lhs, basic_string_view<_CharT, _Traits> __rhs) _NOEXCEPT
         {
            return __lhs.compare(__rhs) >= 0;
         }


         template<class _CharT, class _Traits>
         constexpr inline
            bool operator>=(basic_string_view<_CharT, _Traits> __lhs,
               typename std::common_type<basic_string_view<_CharT, _Traits> >::type __rhs) _NOEXCEPT
         {
            return __lhs.compare(__rhs) >= 0;
         }

         template<class _CharT, class _Traits>
         constexpr inline
            bool operator>=(typename std::common_type<basic_string_view<_CharT, _Traits> >::type __lhs,
               basic_string_view<_CharT, _Traits> __rhs) _NOEXCEPT
         {
            return __lhs.compare(__rhs) >= 0;
         }


         // [string.view.io]
         template<class _CharT, class _Traits>
         basic_ostream<_CharT, _Traits>&
            operator<<(basic_ostream<_CharT, _Traits>& __os, basic_string_view<_CharT, _Traits> __sv)
         {
            return std::__put_character_sequence(__os, __sv.data(), __sv.size());
         }

         typedef basic_string_view<char>     string_view;
         typedef basic_string_view<char16_t> u16string_view;
         typedef basic_string_view<char32_t> u32string_view;
         typedef basic_string_view<wchar_t>  wstring_view;

      }
   }
}

namespace std {

   // [string.view.hash]
   // Shamelessly stolen from <string>
   template<class _CharT, class _Traits>
   struct hash<std::experimental::basic_string_view<_CharT, _Traits> >
      : public unary_function<std::experimental::basic_string_view<_CharT, _Traits>, size_t>
   {
      size_t operator()(const std::experimental::basic_string_view<_CharT, _Traits>& __val) const _NOEXCEPT;
   };

   template<class _CharT, class _Traits>
   size_t
      hash<std::experimental::basic_string_view<_CharT, _Traits> >::operator()(
         const std::experimental::basic_string_view<_CharT, _Traits>& __val) const _NOEXCEPT
   {
      return __do_string_hash(__val.data(), __val.data() + __val.size());
   }

#if _LIBCPP_STD_VER > 11
   template <class _CharT, class _Traits>
   __quoted_output_proxy<_CharT, const _CharT *, _Traits>
      quoted(std::experimental::basic_string_view <_CharT, _Traits> __sv,
         _CharT __delim = _CharT('"'), _CharT __escape = _CharT('\\'))
   {
      return __quoted_output_proxy<_CharT, const _CharT *, _Traits>
         (__sv.data(), __sv.data() + __sv.size(), __delim, __escape);
   }
#endif

}

#endif // _LIBCPP_LFTS_STRING_VIEW