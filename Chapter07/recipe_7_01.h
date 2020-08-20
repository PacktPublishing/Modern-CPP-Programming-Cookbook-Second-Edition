#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <cassert>
#include <iterator>
#include <functional>

namespace recipe_7_01
{
   bool write_data(char const * const filename,
      char const * const data,
      size_t const size)
   {
      auto success = false;
      std::ofstream ofile(filename, std::ios::binary);

      if (ofile.is_open())
      {
         try
         {
            ofile.write(data, size);
            success = true;
         }
         catch (std::ios_base::failure &)
         {
            // handle the error
         }
         ofile.close();
      }

      return success;
   }

   size_t read_data(char const * const filename,
      std::function<char*(size_t const)> allocator)
   {
      size_t readbytes = 0;
      std::ifstream ifile(filename, std::ios::ate | std::ios::binary);
      if (ifile.is_open())
      {
         auto length = static_cast<size_t>(ifile.tellg());
         ifile.seekg(0, std::ios_base::beg);

         auto buffer = allocator(length);

         try
         {
            ifile.read(buffer, length);

            readbytes = static_cast<size_t>(ifile.gcount());
         }
         catch (std::ios_base::failure &)
         {
            // handle the error
         }

         ifile.close();
      }

      return readbytes;
   }

   void execute()
   {
      std::vector<unsigned char> output{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

      {
         std::ofstream ofile("sample.bin", std::ios::binary);
         if (ofile.is_open())
         {
            ofile.write(reinterpret_cast<char*>(output.data()), output.size());
            ofile.close();
         }
      }

      {
         std::vector<unsigned char> input;

         std::ifstream ifile("sample.bin", std::ios::binary);
         if (ifile.is_open())
         {
            ifile.seekg(0, std::ios_base::end);
            auto length = ifile.tellg();
            ifile.seekg(0, std::ios_base::beg);

            input.resize(static_cast<size_t>(length));
            ifile.read(reinterpret_cast<char*>(input.data()), length);

            assert(!ifile.fail() && length == ifile.gcount());

            ifile.close();
         }

         std::cout << (output == input ? "equal" : "not equal") << '\n';
      }

      {
         std::vector<unsigned char> input;

         std::ifstream ifile("sample.bin", std::ios::binary);
         if (ifile.is_open())
         {
            input = std::vector<unsigned char>(
               std::istreambuf_iterator<char>(ifile),
               std::istreambuf_iterator<char>());
            ifile.close();
         }

         std::cout << (output == input ? "equal" : "not equal") << '\n';
      }

      {
         std::vector<unsigned char> input;

         std::ifstream ifile("sample.bin", std::ios::binary);
         if (ifile.is_open())
         {
            ifile.seekg(0, std::ios_base::end);
            auto length = ifile.tellg();
            ifile.seekg(0, std::ios_base::beg);

            input.reserve(static_cast<size_t>(length));
            input.assign(
               std::istreambuf_iterator<char>(ifile),
               std::istreambuf_iterator<char>());
            ifile.close();
         }

         std::cout << (output == input ? "equal" : "not equal") << '\n';
      }

      {
         std::vector<unsigned char> input;

         std::ifstream ifile("sample.bin", std::ios::binary);
         if (ifile.is_open())
         {
            ifile.seekg(0, std::ios_base::end);
            auto length = ifile.tellg();
            ifile.seekg(0, std::ios_base::beg);

            input.reserve(static_cast<size_t>(length));
            std::copy(std::istreambuf_iterator<char>(ifile),
               std::istreambuf_iterator<char>(),
               std::back_inserter(input));
            ifile.close();
         }

         std::cout << (output == input ? "equal" : "not equal") << '\n';
      }

      {
         std::vector<unsigned char> input;

         if (write_data("sample.bin", reinterpret_cast<char*>(output.data()), output.size()))
         {
            if (read_data("sample.bin",
               [&input](size_t const length) {
               input.resize(length);
               return reinterpret_cast<char*>(input.data()); }) > 0)
            {
               std::cout << (output == input ? "equal" : "not equal") << '\n';
            }
         }
      }

      {
         unsigned char* input = nullptr;
         size_t readb = 0;

         if (write_data("sample.bin", reinterpret_cast<char*>(output.data()), output.size()))
         {
            if ((readb = read_data("sample.bin",
               [&input](size_t const length) {
               input = new unsigned char[length];
               return reinterpret_cast<char*>(input);
            })) > 0)
            {
               std::cout << (memcmp(output.data(), input, output.size()) == 0 ? "equal" : "not equal") << '\n';
            }
         }

         delete[] input;
      }
   }
}