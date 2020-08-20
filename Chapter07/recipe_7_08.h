#pragma once

#include <fstream>
#include <iostream>
#include <filesystem>
#include <cassert>

namespace fs = std::filesystem;

namespace recipe_7_08
{
   void execute()
   {
      auto err = std::error_code{};
      auto basepath = fs::current_path();
      auto path = basepath / "temp";

      std::cout << "path: " << basepath << '\n';

      // create directories
      {
         auto success = fs::create_directory(path, err);
         assert(success);

         auto temp = path / "tmp1" / "tmp2" / "tmp3";

         success = fs::create_directory(temp, err);
         assert(!success);
         success = fs::create_directories(temp, err);
         assert(success);
      }

      // move directories
      {
         auto temp = path / "tmp1" / "tmp2" / "tmp3";
         auto newtemp = path / "tmp1" / "tmp3";

         fs::rename(temp, newtemp, err);
         if (err) std::cout << err.message() << '\n';
      }

      // rename directories
      {
         auto temp = path / "tmp1" / "tmp3";
         auto newtemp = path / "tmp1" / "tmp4";

         fs::rename(temp, newtemp, err);
         if (err) std::cout << err.message() << '\n';
      }

      // create test file
      auto filepath = path / "sample.txt";
      {
         std::ofstream f(filepath);
         f.write("sample", 6);
         f.close();
      }

      // create file link
      {
         auto linkpath = path / "sample.txt.link";

         fs::create_symlink(filepath, linkpath, err);
         if (err) std::cout << err.message() << '\n';
      }

      // create directory link
      {
         auto linkdir = basepath / "templink";
         fs::create_directory_symlink(path, linkdir, err);
         if (err) std::cout << err.message() << '\n';
      }

      // copy file
      {
         auto success = fs::copy_file(filepath, path / "sample.bak", err);
         assert(success);
         if (!success) std::cout << err.message() << '\n';

         fs::copy(filepath, path / "sample.cpy", err);
         if (err) std::cout << err.message() << '\n';
      }

      // rename a file
      {
         auto newpath = path / "sample.log";
         fs::rename(filepath, newpath, err);
         if (err) std::cout << err.message() << '\n';
      }

      // move a file
      {
         auto newpath = path / "sample.log";
         fs::rename(newpath, path / "tmp1" / "sample.log", err);
         if (err) std::cout << err.message() << '\n';
      }

      // copy directory
      {
         fs::copy(path, basepath / "temp2", fs::copy_options::recursive, err);
         if (err) std::cout << err.message() << '\n';
      }

      // delete file
      {
         auto success = fs::remove(path / "sample.cpy", err);
         if (!success) std::cout << err.message() << '\n';

         auto linkdir = basepath / "templink";
         success = fs::remove(linkdir, err);
         assert(success);
      }

      // remove directories
      {
         auto temp = path / "tmp1" / "tmp4";
         auto success = fs::remove(temp, err);
         assert(success);

         success = fs::remove_all(path, err) != static_cast<std::uintmax_t>(-1);
         assert(success);
         success = fs::remove_all(basepath / "temp2", err) != static_cast<std::uintmax_t>(-1);
         assert(success);
      }
   }
}