#pragma once

#include <vector>
#include <array>
#include <list>
#include <iostream>
#include <string>
#include <stack>

namespace recipe_5_01
{
   using namespace std::string_literals;

   void process(int const * const arr, size_t const size)
   {
      for (size_t i = 0; i < size; ++i)
         std::cout << arr[i] << '\n';
      std::cout << '\n';
   }

   struct foo
   {
      int a;
      double b;
      std::string c;

      foo(int a, double b, std::string const & c) :
         a(a), b(b), c(c) 
      {}
   };

   void execute()
   {
      {
         std::vector<int> v1{ 1, 2, 3, 4, 5 };

         int arr[] = { 1, 2, 3, 4, 5 };
         std::vector<int> v21(arr, arr + 5);
         std::vector<int> v22(arr + 1, arr + 4);

         std::list<int> l{ 1, 2, 3, 4, 5 };
         std::vector<int> v3(l.begin(), l.end());

         std::vector<int> v4(5, 1);
      }

      {
         std::vector<int> v1{ 1, 2, 3, 4, 5 };
         v1.push_back(6);
         v1.pop_back();

         int arr[] = { 1, 2, 3, 4, 5 };
         std::vector<int> v21;
         v21.insert(v21.begin(), arr, arr + 5);
         std::vector<int> v22;
         v22.insert(v22.begin(), arr, arr + 3);

         std::vector<foo> v3;
         v3.emplace_back(1, 1.0, "one"s);
         v3.emplace(v3.begin(), 2, 2.0, "two"s);    
      }

      {
         std::vector<int> v1{ 1, 2, 3, 4, 5 };
         std::vector<int> v2{ 10, 20, 30 };
         v2 = v1;
      
         int arr[] = { 1, 2, 3, 4, 5 };
         std::vector<int> v31;
         v31.assign(arr, arr + 5);
         std::vector<int> v32;
         v32.assign(arr + 1, arr + 4);

         std::vector<int> v4{ 1, 2, 3, 4, 5 };
         std::vector<int> v5{ 10, 20, 30 };
         v4.swap(v5);

         std::vector<int> v6{ 1, 2, 3, 4, 5 };
         v6.clear();

         std::vector<int> v7{ 1, 2, 3, 4, 5 };
         v7.erase(v7.begin() + 2, v7.begin() + 4);
      }

      {
         std::vector<int> v{ 1, 2, 3, 4, 5 };
         
         process(v.data(), v.size());
         process(&v[0], v.size());
         process(&v.front(), v.size());
         process(&*v.begin(), v.size());
      }

      {
         std::list<int> l { 1, 2, 3, 4, 5 };
         std::vector<int> v(l.begin(), l.end());
         process(v.data(), v.size());
      }

      {
         std::vector<int> v{ 1, 2, 3, 4, 5 };
         std::vector<int>().swap(v);
      }
   }
}