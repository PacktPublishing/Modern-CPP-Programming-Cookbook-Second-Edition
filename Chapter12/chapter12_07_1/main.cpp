#include <iostream>

#include <cppcoro/task.hpp>
#include <cppcoro/sync_wait.hpp>

cppcoro::task<int> get_answer()
{
  co_return 42;
}

cppcoro::task<> print_answer()
{
  auto t = co_await get_answer();
  std::cout << "the answer is " << t << '\n';
}

cppcoro::task<int&> get_answer(int& a)
{
  std::cout << "ref answering...\n";
  a++;
  co_return a;
}

cppcoro::task<> say_hello()
{
  std::cout << "hello, world!\n";
  co_return;
}

cppcoro::task<> demo()
{
  std::cout << "starting...\n";
  co_await say_hello();

  std::cout << "asking...\n";
  auto t = co_await get_answer();
  std::cout << "the answer is " << t << '\n';

  int a = 42;
  std::cout << "asking...\n";
  int& b = co_await get_answer(a);
  std::cout << "the answer is " << b << '\n';
  b++;
  std::cout << "the answer is (a) " << a << '\n';
  std::cout << "the answer is (b) " << b << '\n';

  co_await print_answer();
}

int main()
{   
   cppcoro::sync_wait(demo());
}
