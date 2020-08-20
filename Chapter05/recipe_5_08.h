#pragma once

#include <vector>
#include <algorithm>
#include <string>

namespace recipe_5_08
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
         std::vector<int> v1{ 1, 2, 3, 4, 4, 5 };
         std::vector<int> v2{ 2, 3, 3, 4, 6, 8 };
         std::vector<int> v3;
         
         std::set_union(
            v1.cbegin(), v1.cend(),
            v2.cbegin(), v2.cend(),
            std::back_inserter(v3));

         // v3 = {1, 2, 3, 3, 4, 4, 5, 6, 8}
      }

      {
         std::vector<int> v1{ 1, 2, 3, 4, 4, 5 };
         std::vector<int> v2{ 2, 3, 3, 4, 6, 8 };
         std::vector<int> v3;

         std::merge(
            v1.cbegin(), v1.cend(),
            v2.cbegin(), v2.cend(),
            std::back_inserter(v3));

         // v3 = {1, 2, 2, 3, 3, 3, 4, 4, 4, 5, 6, 8}
      }

      {
         std::vector<int> v1{ 1, 2, 3, 4, 4, 5 };
         std::vector<int> v2{ 2, 3, 3, 4, 6, 8 };
         std::vector<int> v3;

         std::set_intersection(
            v1.cbegin(), v1.cend(),
            v2.cbegin(), v2.cend(),
            std::back_inserter(v3));

         // v3 = {2, 3, 4}
      }

      {
         std::vector<int> v1{ 1, 2, 3, 4, 4, 5 };
         std::vector<int> v2{ 2, 3, 3, 4, 6, 8 };
         std::vector<int> v3;

         std::set_difference(
            v1.cbegin(), v1.cend(),
            v2.cbegin(), v2.cend(),
            std::back_inserter(v3));

         // v3 = {1, 4, 5}
      }

      {
         std::vector<int> v1{ 1, 2, 3, 4, 4, 5 };
         std::vector<int> v2{ 2, 3, 3, 4, 6, 8 };
         std::vector<int> v3;

         std::set_symmetric_difference(
            v1.cbegin(), v1.cend(),
            v2.cbegin(), v2.cend(),
            std::back_inserter(v3));

         // v3 = {1, 3, 4, 5, 6, 8}
      }

      {
         std::vector<int> v1{ 1, 2, 3, 4, 4, 5 };
         std::vector<int> v2{ 2, 3, 3, 4, 6, 8 };
         std::vector<int> v3{ 1, 2, 4 };
         std::vector<int> v4{  };

         auto i1 = std::includes(v1.cbegin(), v1.cend(), 
                                 v2.cbegin(), v2.cend()); // i1 = false
         auto i2 = std::includes(v1.cbegin(), v1.cend(), 
                                 v3.cbegin(), v3.cend()); // i2 = true
         auto i3 = std::includes(v1.cbegin(), v1.cend(), 
                                 v4.cbegin(), v4.cend()); // i3 = true
      }

      {
         std::vector<Task> v1{
            { 10, "Task 1.1"s },
            { 20, "Task 1.2"s },
            { 20, "Task 1.3"s },
            { 20, "Task 1.4"s },
            { 30, "Task 1.5"s },
            { 50, "Task 1.6"s },
         };

         std::vector<Task> v2{
            { 20, "Task 2.1"s },
            { 30, "Task 2.2"s },
            { 30, "Task 2.3"s },
            { 30, "Task 2.4"s },
            { 40, "Task 2.5"s },
            { 50, "Task 2.6"s },
         };

         std::vector<Task> v3;
         std::set_union(
            v1.cbegin(), v1.cend(),
            v2.cbegin(), v2.cend(),
            std::back_inserter(v3));
         // v3 = {{ 10, "Task 1.1" },{ 20, "Task 1.2" },{ 20, "Task 1.3" },
         //       { 20, "Task 1.4" },{ 30, "Task 1.5" },{ 30, "Task 2.3" },
         //       { 30, "Task 2.4" },{ 40, "Task 2.5" },{ 50, "Task 1.6" }}

         std::vector<Task> v4;
         std::merge(
            v1.cbegin(), v1.cend(),
            v2.cbegin(), v2.cend(),
            std::back_inserter(v4));
         // v4 = {{ 10, "Task 1.1" },{ 20, "Task 1.2" },{ 20, "Task 1.3" },
         //       { 20, "Task 1.4" },{ 20, "Task 2.1" },{ 30, "Task 1.5" },
         //       { 30, "Task 2.2" },{ 30, "Task 2.3" },{ 30, "Task 2.4" },
         //       { 40, "Task 2.5" },{ 50, "Task 1.6" },{ 50, "Task 2.6" }}
    
         std::vector<Task> v5;
         std::set_intersection(
            v1.cbegin(), v1.cend(),
            v2.cbegin(), v2.cend(),
            std::back_inserter(v5));
         // v5 = {{ 20, "Task 1.2" },{ 30, "Task 1.5" },{ 50, "Task 1.6" }}

         std::vector<Task> v6;
         std::set_difference(
            v1.cbegin(), v1.cend(),
            v2.cbegin(), v2.cend(),
            std::back_inserter(v6));
         // v6 = {{ 10, "Task 1.1" },{ 20, "Task 1.3" },{ 20, "Task 1.4" }}

         std::vector<Task> v7;
         std::set_symmetric_difference(
            v1.cbegin(), v1.cend(),
            v2.cbegin(), v2.cend(),
            std::back_inserter(v7));
         // v7 = {{ 10, "Task 1.1" },{ 20, "Task 1.3" },{ 20, "Task 1.4" }
         //       { 30, "Task 2.3" },{ 30, "Task 2.4" },{ 40, "Task 2.5" }}

      }
   }
}