#pragma once

#include <vector>
#include <algorithm>

namespace recipe_9_09
{
   class Buffer
   {
      unsigned char* ptr;
      size_t         length;
   public:
      Buffer(): ptr(nullptr), length(0)
      {}

      explicit Buffer(size_t const size)
         :ptr(new unsigned char[size] {0}), length(size)
      {}

      ~Buffer()
      {
         delete[] ptr;
      }

      Buffer(Buffer const& other):
         ptr(new unsigned char[other.length]),
         length(other.length)
      {
         std::copy(other.ptr, other.ptr + other.length, ptr);
      }

      Buffer& operator=(Buffer const& other)
      {
         if (this != &other)
         {
            delete[] ptr;

            ptr = new unsigned char[other.length];
            length = other.length;

            std::copy(other.ptr, other.ptr + other.length, ptr);
         }

         return *this;
      }

      Buffer(Buffer&& other)
      {
         // copy
         ptr = other.ptr;
         length = other.length;

         // reset
         other.ptr = nullptr;
         other.length = 0;
      }

      /*
      Buffer(Buffer&& other)
         :ptr(nullptr),length(0)
      {
         *this = std::move(other);
      }
      */

      Buffer& operator=(Buffer&& other)
      {
         if (this != &other)
         {
            // clean up existing resources
            delete[] ptr;

            // copy
            ptr = other.ptr;
            length = other.length;

            // reset
            other.ptr = nullptr;
            other.length = 0;
         }

         return *this;
      }

      size_t size() const         { return length;}
      unsigned char* data() const { return ptr; }
   };

   void execute()
   {
      {
         std::vector<Buffer> c;
         c.push_back(Buffer(100));  // move

         Buffer b(200);
         c.push_back(b);            // copy
         c.push_back(std::move(b)); // move
      }

      {
         Buffer b1;                 // default constructor
         Buffer b2(100);            // explicit constructor
         Buffer b3(b2);             // copy constructor
         b1 = b3;                   // assignment operator
         Buffer b4(std::move(b1));  // move constructor
         b3 = std::move(b4);        // move assignment
      }
   }
}