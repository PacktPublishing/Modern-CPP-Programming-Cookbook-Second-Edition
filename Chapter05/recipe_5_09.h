#pragma once

#include <vector>
#include <algorithm>
#include <string>

namespace recipe_5_09
{
   void execute()
   {
      {
         std::vector<int> v{ 1,2,3,4,5 };
         std::fill_n(std::back_inserter(v), 3, 0);

         // v={1,2,3,4,5,0,0,0}
      }

      {
         std::list<int> l{ 1,2,3,4,5 };
         std::fill_n(std::front_inserter(l), 3, 0);

         // l={0,0,0,1,2,3,4,5}
      }

      {
         std::vector<int> v{ 1,2,3,4,5 };
         std::fill_n(std::inserter(v, v.begin()), 3, 0);

         // v={0,0,0,1,2,3,4,5}
      }

      {
         std::list<int> l{ 1,2,3,4,5 };
         auto it = l.begin();
         std::advance(it, 3);

         std::fill_n(std::inserter(l, it), 3, 0);

         // l={1,2,3,0,0,0,4,5}
      }

      {
         std::vector<int> v{ 1,2,3,4,5 };
         std::back_insert_iterator<std::vector<int>> it(v);
         *it = 6;
      }

      {
         std::list<int> l{ 1,2,3,4,5 };
         std::front_insert_iterator<std::list<int>> it(l);
         *it = 0;
      }

      {
         std::vector<int> v{ 1,2,3,4,5 };
         *std::back_inserter(v) = 6;
      }

      {
         std::list<int> l{ 1,2,3,4,5 };
         *std::front_inserter(l) = 0;
      }
   }
}