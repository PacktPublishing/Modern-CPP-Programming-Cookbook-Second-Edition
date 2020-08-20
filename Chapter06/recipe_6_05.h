#pragma once

#include <string>
#include <iostream>
#include <set>
#include <unordered_set>

namespace recipe_6_05
{
   using namespace std::string_literals;

   struct Item
   {
      int         id;
      std::string name;
      double      value;

      Item(int const id, std::string const & name, double const value)
         :id(id), name(name), value(value)
      {}
      
      bool operator==(Item const & other) const
      {
         return 
            id == other.id &&
            name == other.name &&
            value == other.value;
      }
      
      bool operator!=(Item const & other) const
      {
         return !(*this == other);
      }

      bool operator<(Item const & other) const
      {
         return id < other.id &&
                name < other.name &&
                value < other.value;
      }
   };
}

namespace std
{
   template<>
   struct hash<recipe_6_05::Item>
   {
      typedef recipe_6_05::Item  argument_type;
      typedef size_t             result_type;

      result_type operator()(argument_type const & item) const
      {
         result_type hashValue = 17;
         hashValue = 31 * hashValue + std::hash<int>{}(item.id);
         hashValue = 31 * hashValue + std::hash<std::string>{}(item.name);
         hashValue = 31 * hashValue + std::hash<double>{}(item.value);

         return hashValue;
      }
   };
}

namespace recipe_6_05
{
   void execute()
   {
      std::set<Item> set1
      { 
         { 1, "one"s, 1.0 }, 
         { 2, "two"s, 2.0 },
         { 3, "three"s, 3.0 },
      };
      
      std::unordered_set<Item> set2
      {
         { 1, "one"s, 1.0 },
         { 2, "two"s, 2.0 },
         { 3, "three"s, 3.0 },
      };
   }
}