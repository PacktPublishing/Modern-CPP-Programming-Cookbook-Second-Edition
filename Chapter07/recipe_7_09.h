#pragma once

#include <fstream>
#include <iostream>
#include <filesystem>
#include <cassert>

namespace fs = std::filesystem;

namespace recipe_7_09
{
   void execute()
   {
      auto path = fs::current_path();
      auto initialpath = path / "sample.plays";
      assert(fs::exists(initialpath));

      auto filepath = path / "sample.dat";
      auto temppath = path / "sample.tmp";
      auto err = std::error_code{};

      // make a copy of the original file
      {
         auto success = fs::copy_file(initialpath, filepath, err);
         if (!success || err)
         {
            std::cout << err.message() << '\n';
            return;
         }
      }

      // remove content from file
      {
         std::ifstream in(filepath);
         if (!in.is_open())
         {
            std::cout << "File could not be opened!" << '\n';
            return;
         }

         std::ofstream out(temppath, std::ios::trunc);
         if (!out.is_open())
         {
            std::cout << "Temporary file could not be created!" << '\n';
            return;
         }

         auto line = std::string{};
         while (std::getline(in, line))
         {
            if (!line.empty() && line.at(0) != ';')
            {
               out << line << '\n';
            }
         }

         in.close();
         out.close();

         auto success = fs::remove(filepath, err);
         if(!success || err)
         {
            std::cout << err.message() << '\n';
            return;
         }

         fs::rename(temppath, filepath, err);
         if (err)
         {
            std::cout << err.message() << '\n';
         }
      }

      // clean up
      {
         auto success = fs::remove(filepath, err);
         if (!success || err)
         {
            std::cout << err.message() << '\n';
         }
      }
   }
}