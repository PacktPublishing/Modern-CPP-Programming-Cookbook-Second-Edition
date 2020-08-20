#pragma once

#include <map>
#include <iostream>

namespace recipe_1_13
{
   std::tuple<int, std::string, double> find()
   {
      return std::make_tuple(1, "marius", 1234.5);
   }

   struct foo
   {
      int         id;
      std::string name;
   };

   void execute()
   {
      {
         std::map<int, std::string> m;

         auto result = m.insert({ 1, "one" });
         std::cout << "inserted = " << result.second << '\n'
            << "value = " << result.first->second << '\n';
      }

      {
         std::map<int, std::string> m;
         std::map<int, std::string>::iterator it;
         bool inserted;

         std::tie(it, inserted) = m.insert({ 1, "one" });
         std::cout << "inserted = " << inserted << '\n'
            << "value = " << it->second << '\n';

         std::tie(it, inserted) = m.insert({ 1, "two" });
         std::cout << "inserted = " << inserted << '\n'
            << "value = " << it->second << '\n';
      }

      {
         int id;
         std::string name;
         double score;

         std::tie(id, name, score) = find();

         std::cout << "id=" << id
            << " name=" << name
            << " score=" << score << '\n';
      }

      {
         std::map<int, std::string> m;
         if (auto[it, inserted] = m.insert({ 1, "two" }); inserted)
         {
            std::cout << it->second << '\n';
         }

         {
            auto[it, inserted] = m.insert({ 1, "one" });
            std::cout << "inserted = " << inserted << '\n'
                      << "value = " << it->second << '\n';
         }

         {
            auto[it, inserted] = m.insert({ 1, "two" });
            std::cout << "inserted = " << inserted << '\n'
                      << "value = " << it->second << '\n';
         }

         auto[id, name, score] = find();

         if (auto[id, name, score] = find(); score > 1000)
         {
            std::cout << name << '\n';
         }
      }

      {
         foo f{ 42, "john" };
         auto [i, n] = f;
         auto& [ri, rn] = f;

         f.id = 43;

         std::cout << f.id << ' ' << f.name << '\n';   // 43 john
         std::cout << i << ' ' << n << '\n';           // 42 john
         std::cout << ri << ' ' << rn << '\n';         // 43 john

      }

#ifdef HAS_STRUCTURED_BINDINGS_CAPTURES
      {
         foo f{ 42, "john" };
         auto [i, n] = f;
         auto l1 = [i] {std::cout << i; };
         auto l2 = [=] {std::cout << i; };
         auto l3 = [&i] {std::cout << i; };
         auto l4 = [&] {std::cout << i; };
      }
#endif
   }
}