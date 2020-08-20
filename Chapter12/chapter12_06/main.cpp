#include <iostream>
#include <fstream>
#include <string>
#include <string_view>
#include <vector>
#include <algorithm>
#include <map>
#include <cmath>
#include <algorithm>
#include <assert.h>

#ifdef USE_RANGES_V3
#include "range/v3/view.hpp"
#include "range/v3/algorithm/sort.hpp"
#include "range/v3/algorithm/copy.hpp"
#include "range/v3/algorithm/reverse.hpp"
#include "range/v3/algorithm/count_if.hpp"
#include "range/v3/algorithm/max.hpp"

namespace rv = ranges::views;
namespace rg = ranges;

template<class T>
struct ranges_ostream_iterator : std::ostream_iterator<T>
{
   using std::ostream_iterator<T>::ostream_iterator;
   ranges_ostream_iterator() : std::ostream_iterator<T>{ std::cout } {}
   ranges_ostream_iterator& operator++() { std::ostream_iterator<T>::operator++(); return *this; }
   ranges_ostream_iterator& operator++(int) { return operator++(); }
   using difference_type = int;
   int operator-(ranges_ostream_iterator const&) { return 0; }
};

#define VIEW_CONCEPT rg::view_
#define OSTREAM_ITERATOR ranges_ostream_iterator

#else
#include <ranges>

namespace rv = std::views;
namespace rg = std::ranges;

#define VIEW_CONCEPT rg::view
#define OSTREAM_ITERATOR std::ostream_iterator
#endif

template<rg::input_range R, typename P> requires VIEW_CONCEPT<R>
class trim_view : public rg::view_interface<trim_view<R, P>>
{
private:
   R base_{};
   P pred_;
   mutable rg::iterator_t<R> begin_{ std::begin(base_) };
   mutable rg::iterator_t<R> end_{ std::end(base_) };
   mutable bool evaluated_ = false;

private:
   void ensure_evaluated() const
   {
      if (!evaluated_)
      {
         while (begin_ != std::end(base_) && pred_(*begin_)) { begin_ = std::next(begin_); }
         while (end_ != begin_ && pred_(*std::prev(end_))) { end_ = std::prev(end_); }
         evaluated_ = true;
      }
   }

public:
   trim_view() = default;

   constexpr trim_view(R base, P pred)
      : base_(std::move(base))
      , pred_(std::move(pred))
      , begin_(std::begin(base_))
      , end_(std::end(base_))
   {}

   constexpr R base() const& { return base_; }
   constexpr R base()&& { return std::move(base_); }
   constexpr P const& pred() const { return pred_; }

   constexpr auto begin() const
   {
      ensure_evaluated(); return begin_;
   }
   constexpr auto end() const
   {
      ensure_evaluated(); return end_;
   }

   constexpr auto size() requires rg::sized_range<R>
   { return std::distance(begin_, end_); }
   constexpr auto size() const requires rg::sized_range<const R>
   { return std::distance(begin_, end_); }
};

template<class R, typename P>
trim_view(R&& base, P pred)
   ->trim_view<rg::views::all_t<R>, P>;

namespace details
{
   template <typename P>
   struct trim_view_range_adaptor_closure
   {
      P pred_;
      constexpr trim_view_range_adaptor_closure(P pred)
         : pred_(pred)
      {}

      template <rg::viewable_range R>
      constexpr auto operator()(R&& r) const
      {
         return trim_view(std::forward<R>(r), pred_);
      }
   };

   struct trim_view_range_adaptor
   {
      template<rg::viewable_range R, typename P>
      constexpr auto operator () (R&& r, P pred)
      {
         return trim_view(std::forward<R>(r), pred);
      }

      template <typename P>
      constexpr auto operator () (P pred)
      {
         return trim_view_range_adaptor_closure(pred);
      }
   };

   template <rg::viewable_range R, typename P>
   constexpr auto operator | (R&& r, trim_view_range_adaptor_closure<P> const& a)
   {
      return a(std::forward<R>(r));
   }
}

namespace views
{
   inline static details::trim_view_range_adaptor trim;
}

// -------- tests

template <typename P>
void are_equal(std::vector<int> const& input, std::vector<int> const& output, P&& pred)
{
   std::size_t index = 0;
   for (auto i : input | views::trim(std::forward<P>(pred)))
   {
      assert(i == output[index]);
      index++;
   }
   assert(index == output.size());
}

template <typename P>
void are_equal_reverse1(std::vector<int> const& input, std::vector<int> const& output, P&& pred)
{
   std::size_t index = 0;
   for (auto i : input | rg::views::reverse | views::trim(std::forward<P>(pred)))
   {
      assert(i == output[index]);
      index++;
   }
   assert(index == output.size());
}

template <typename P>
void are_equal_reverse2(std::vector<int> const& input, std::vector<int> const& output, P&& pred)
{
   std::size_t index = 0;
   for (auto i : input | views::trim(std::forward<P>(pred)) | rg::views::reverse)
   {
      assert(i == output[index]);
      index++;
   }
   assert(index == output.size());
}

int main()
{
   auto is_odd = [](int const n) {return n % 2 == 1; };

   are_equal({}, {}, is_odd);
   are_equal({ 1 }, {}, is_odd);
   are_equal({ 1,3,5 }, {}, is_odd);
   are_equal({ 2 }, { 2 }, is_odd);
   are_equal({ 2,4 }, { 2,4 }, is_odd);
   are_equal({ 2,3,4 }, { 2,3,4 }, is_odd);
   are_equal({ 1,2,3,4 }, { 2,3,4 }, is_odd);
   are_equal({ 1,1,2,3,4 }, { 2,3,4 }, is_odd);
   are_equal({ 2,3,4,5 }, { 2,3,4 }, is_odd);
   are_equal({ 2,3,4,5,5 }, { 2,3,4 }, is_odd);
   are_equal({ 1,2,3,4,5 }, { 2,3,4 }, is_odd);
   are_equal({ 1,1,2,3,4,5,5 }, { 2,3,4 }, is_odd);

   are_equal_reverse1({}, {}, is_odd);
   are_equal_reverse1({ 1 }, {}, is_odd);
   are_equal_reverse1({ 1,3,5 }, {}, is_odd);
   are_equal_reverse1({ 2 }, { 2 }, is_odd);
   are_equal_reverse1({ 2,4 }, { 4,2 }, is_odd);
   are_equal_reverse1({ 2,3,4 }, { 4,3,2 }, is_odd);
   are_equal_reverse1({ 1,2,3,4 }, { 4,3,2 }, is_odd);
   are_equal_reverse1({ 1,1,2,3,4 }, { 4,3,2 }, is_odd);
   are_equal_reverse1({ 2,3,4,5 }, { 4,3,2 }, is_odd);
   are_equal_reverse1({ 2,3,4,5,5 }, { 4,3,2 }, is_odd);
   are_equal_reverse1({ 1,2,3,4,5 }, { 4,3,2 }, is_odd);
   are_equal_reverse1({ 1,1,2,3,4,5,5 }, { 4,3,2 }, is_odd);

   are_equal_reverse2({}, {}, is_odd);
   are_equal_reverse2({ 1 }, {}, is_odd);
   are_equal_reverse2({ 1,3,5 }, {}, is_odd);
   are_equal_reverse2({ 2 }, { 2 }, is_odd);
   are_equal_reverse2({ 2,4 }, { 4,2 }, is_odd);
   are_equal_reverse2({ 2,3,4 }, { 4,3,2 }, is_odd);
   are_equal_reverse2({ 1,2,3,4 }, { 4,3,2 }, is_odd);
   are_equal_reverse2({ 1,1,2,3,4 }, { 4,3,2 }, is_odd);
   are_equal_reverse2({ 2,3,4,5 }, { 4,3,2 }, is_odd);
   are_equal_reverse2({ 2,3,4,5,5 }, { 4,3,2 }, is_odd);
   are_equal_reverse2({ 1,2,3,4,5 }, { 4,3,2 }, is_odd);
   are_equal_reverse2({ 1,1,2,3,4,5,5 }, { 4,3,2 }, is_odd);

   std::vector<int> n{ 1,1,2,3,4,5,6,7,7,9 };

   {
      auto v = trim_view(n, is_odd);
      rg::copy(v, OSTREAM_ITERATOR<int>(std::cout, " "));
      std::cout << '\n';

      for (auto i : rv::reverse(trim_view(n, is_odd)))
         std::cout << i << ' ';
      std::cout << '\n';
   }

   {
      auto v = n | views::trim(is_odd);
      rg::copy(v, OSTREAM_ITERATOR<int>(std::cout, " "));
      std::cout << '\n';

      for (auto i : n | views::trim(is_odd) | rv::reverse)
         std::cout << i << ' ';
      std::cout << '\n';

   }
}