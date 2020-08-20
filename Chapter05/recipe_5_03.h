#pragma once

#include <vector>
#include <iostream>

namespace recipe_5_03
{
   class bitvector
   {
      std::vector<bool> bv;
   public:
      bitvector() = default;
      bitvector(bitvector const&) = default;
      bitvector(bitvector&&) = default;
      bitvector& operator=(bitvector const&) = default;
      bitvector& operator=(bitvector&&) = default;

      bitvector(std::vector<bool> const& bv) : bv(bv) {}
      bool operator[](size_t const i) { return bv[i]; }

      inline bool any() const {
         for (auto b : bv) if (b) return true;
         return false;
      }

      inline bool all() const {
         for (auto b : bv) if (!b) return false;
         return true;
      }

      inline bool none() const { return !any(); }

      inline size_t count() const {
         return std::count(bv.cbegin(), bv.cend(), true);
      }

      inline size_t size() const { return bv.size(); }

      inline bitvector& add(bool const value) {
         bv.push_back(value);
         return *this;
      }

      inline bitvector& remove(size_t const index) {
         if (index >= bv.size())
            throw std::out_of_range("Index out of range");
         bv.erase(bv.begin() + index);
         return *this;
      }

      inline bitvector& set(bool const value = true) {
         for (size_t i = 0; i < bv.size(); ++i)
            bv[i] = value;
         return *this;
      }

      inline bitvector& set(size_t const index, bool const value = true) {
         if (index >= bv.size())
            throw std::out_of_range("Index out of range");
         bv[index] = value;
         return *this;
      }

      inline bitvector& reset() {
         for (size_t i = 0; i < bv.size(); ++i) bv[i] = false;
         return *this;
      }

      inline bitvector& reset(size_t const index) {
         if (index >= bv.size())
            throw std::out_of_range("Index out of range");
         bv[index] = false;
         return *this;
      }

      inline bitvector& flip() {
         bv.flip();
         return *this;
      }

      std::vector<bool>& data() { return bv; }
   };

   void execute()
   {
      {
         // create an empty vector
         std::vector<bool> bv;      // []

         // add bits to the vector
         bv.push_back(true);        // [1]
         bv.push_back(true);        // [1, 1]
         bv.push_back(false);       // [1, 1, 0]
         bv.push_back(false);       // [1, 1, 0, 0]
         bv.push_back(true);        // [1, 1, 0, 0, 1]

         // set values of individual bits
         bv[3] = true;              // [1, 1, 0, 1, 1]

         // use generic algorithms
         auto count_of_ones = std::count(bv.cbegin(), bv.cend(), true);

         // remove a bit from the vector
         bv.erase(bv.begin() + 2);  // [1, 1, 1, 1]
      }

      {
         std::vector<bool> bv;
         bv.resize(10);
         // auto& bit1 = bv[0]; // error
         // auto& bit2 = *bv.begin(); // error
      }

      {
         bitvector bv;
         bv.add(true).add(true).add(false);  // [1, 1, 0]
         bv.add(false);                      // [1, 1, 0, 0]
         bv.add(true);                       // [1, 1, 0, 0, 1]

         if (bv.any()) std::cout << "has some 1s" << '\n';
         if (bv.all()) std::cout << "has only 1s" << '\n';
         if (bv.none()) std::cout << "has no 1s" << '\n';
         std::cout << "has " << bv.count() << " 1s" << '\n';

         bv.set(2, true);  // [1, 1, 1, 0, 1]
         bv.set();         // [1, 1, 1, 1, 1]

         bv.reset(0);      // [0, 1, 1, 1, 1]
         bv.reset();       // [0, 0, 0, 0, 0]

         bv.flip();        // [1, 1, 1, 1, 1]
      }
   }
}