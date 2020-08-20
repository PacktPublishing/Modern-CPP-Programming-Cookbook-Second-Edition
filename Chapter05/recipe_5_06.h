#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <functional>

namespace recipe_5_06
{
   using namespace std::string_literals;

   struct Task
   {
      int priority;
      std::string name;
   };

   bool operator<(Task const & lhs, Task const & rhs) {
      return lhs.priority < rhs.priority;
   }

   bool operator>(Task const & lhs, Task const & rhs) {
      return lhs.priority > rhs.priority;
   }

   void execute()
   {
      {
         std::vector<int> v{3, 13, 5, 8, 1, 2, 1};

         std::sort(v.begin(), v.end());
         // v = {1, 1, 2, 3, 5, 8, 13}

         std::sort(v.begin(), v.end(), std::greater<>());
         // v = {13, 8, 5, 3, 2, 1 ,1}
      }

      {
         std::vector<Task> v{ 
            { 10, "Task 1"s },
            { 40, "Task 2"s },
            { 25, "Task 3"s },
            { 10, "Task 4"s },
            { 80, "Task 5"s },
            { 10, "Task 6"s },
         };

         std::stable_sort(v.begin(), v.end());
         // {{ 10, "Task 1" },{ 10, "Task 4" },{ 10, "Task 6" },
         //  { 25, "Task 3" },{ 40, "Task 2" },{ 80, "Task 5" }}

         std::stable_sort(v.begin(), v.end(), std::greater<>());
         // {{ 80, "Task 5" },{ 40, "Task 2" },{ 25, "Task 3" },
         //  { 10, "Task 1" },{ 10, "Task 4" },{ 10, "Task 6" }}
      }

      {
         std::vector<int> v{ 3, 13, 5, 8, 1, 2, 1 };

         std::partial_sort(v.begin(), v.begin() + 4, v.end());
         // v = {1, 1, 2, 3, ?, ?, ?}

         std::partial_sort(v.begin(), v.begin() + 4, v.end(), std::greater<>());
         // v = {13, 8, 5, 3, ?, ?, ?}
      }

      {
         std::vector<int> v{ 3, 13, 5, 8, 1, 2, 1 };
         std::vector<int> vc(v.size());

         std::partial_sort_copy(v.begin(), v.end(), vc.begin(), vc.end());
         // v  = {3, 13, 5, 8, 1, 2, 1}
         // vc = {1, 1, 2, 3, 5, 8, 13}

         std::partial_sort_copy(v.begin(), v.end(), vc.begin(), vc.end(), std::greater<>());
         // vc = {13, 8, 5, 3, 2, 1, 1}
      }

      {
         std::vector<int> v{ 3, 13, 5, 8, 1, 2, 1 };

         std::nth_element(v.begin(), v.begin() + 3, v.end());
         // v = {1, 1, 2, 3, 5, 8, 13}

         std::nth_element(v.begin(), v.begin() + 3, v.end(), std::greater<>());
         // v = {13, 8, 5, 3, 2, 1, 1}
      }

      {
         std::vector<int> v { 1, 1, 2, 3, 5, 8, 13 };

         auto sorted = std::is_sorted(v.cbegin(), v.cend());

         sorted = std::is_sorted(v.cbegin(), v.cend(), std::greater<>());
      }

      {
         std::vector<int> v{ 3, 13, 5, 8, 1, 2, 1 };

         auto it = std::is_sorted_until(v.cbegin(), v.cend());

         auto length = std::distance(v.cbegin(), it);
      }
   }
}