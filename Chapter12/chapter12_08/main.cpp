#ifdef _MSC_VER
#include <experimental/coroutine>
namespace stdco = std::experimental;
#else
#include <coroutine>
namespace stdco = std;
#endif

#include <memory>
#include <iostream>
#include <optional>

template <typename T>
struct generator
{
   struct promise_type
   {
      T const* value_;
      std::exception_ptr   eptr_;

      auto get_return_object() { return generator{ *this }; }

      auto initial_suspend() noexcept { return stdco::suspend_always{}; }
      auto final_suspend() noexcept { return stdco::suspend_always{}; }

      void unhandled_exception() noexcept
      {
         eptr_ = std::current_exception();
      }

      void rethrow_if_exception()
      {
         if (eptr_)
         {
            std::rethrow_exception(eptr_);
         }
      }

      auto yield_value(T const& v)
      {
         value_ = std::addressof(v);
         return stdco::suspend_always{};
      }

      void return_void() {}

      template <typename U>
      U&& await_transform(U&& v)
      {
         return std::forward<U>(v);
      }
   };

   struct iterator
   {
      using iterator_category = std::input_iterator_tag;
      using difference_type = ptrdiff_t;
      using value_type = T;
      using reference = T const&;
      using pointer = T const*;

      stdco::coroutine_handle<promise_type> handle_ = nullptr;

      iterator() = default;
      iterator(nullptr_t) : handle_(nullptr) {}

      iterator(stdco::coroutine_handle<promise_type> arg) : handle_(arg) {}

      iterator& operator++()
      {
         handle_.resume();
         if (handle_.done())
         {
            std::exchange(handle_, {}).promise().rethrow_if_exception();
         }

         return *this;
      }

      void operator++(int)
      {
         ++* this;
      }

      bool operator==(iterator const& _Right) const
      {
         return handle_ == _Right.handle_;
      }

      bool operator!=(iterator const& _Right) const
      {
         return !(*this == _Right);
      }

      reference operator*() const
      {
         return *handle_.promise().value_;
      }

      pointer operator->() const
      {
         return std::addressof(handle_.promise().value_);
      }
   };

   explicit generator(promise_type& p)
      : handle_(stdco::coroutine_handle<promise_type>::from_promise(p))
   {}

   generator() = default;
   generator(generator const&) = delete;
   generator& operator=(generator const&) = delete;

   generator(generator&& other) : handle_(other.handle_)
   {
      other.handle_ = nullptr;
   }

   generator& operator=(generator&& other)
   {
      if (this != std::addressof(other))
      {
         handle_ = other.handle_;
         other.handle_ = nullptr;
      }
      return *this;
   }

   ~generator()
   {
      if (handle_)
      {
         handle_.destroy();
      }
   }

   iterator begin()
   {
      if (handle_)
      {
         handle_.resume();
         if (handle_.done())
         {
            handle_.promise().rethrow_if_exception();
            return { nullptr };
         }
      }

      return { handle_ };
   }

   iterator end()
   {
      return { nullptr };
   }
private:
   stdco::coroutine_handle<promise_type> handle_ = nullptr;
};

generator<int> get_values() noexcept
{
   co_yield 1;
   co_yield 2;
   co_yield 3;
}

generator<int> iota(int start = 0, int step = 1) noexcept
{
   auto value = start;
   for (int i = 0;; ++i)
   {
      co_yield value;
      value += step;
   }
}

generator<std::optional<int>> iota_n(int start = 0, int step = 1, int n = std::numeric_limits<int>::max()) noexcept
{
   auto value = start;
   for (int i = 0; i < n; ++i)
   {
      co_yield value;
      value += step;
   }
}

generator<int> fibonacci() noexcept
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

   c = 1;
   std::cout << "fibonacci:";
   for (auto i : fibonacci())
   {
      std::cout << i << ' ';
      if (++c > 10) break;
   }
   std::cout << '\n';
}