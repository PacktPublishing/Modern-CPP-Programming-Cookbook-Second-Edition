#pragma once

#include <iostream>
#include <filesystem>
#include <functional>

namespace fs = std::filesystem;

namespace recipe_7_12
{
   std::vector<fs::path> find_files(
      fs::path const & dir, 
      std::function<bool(fs::path const&)> filter)
   {
      auto result = std::vector<fs::path>{};

      if (fs::exists(dir))
      {
         for (auto const & entry : 
            fs::recursive_directory_iterator(
               dir, 
               fs::directory_options::follow_directory_symlink))
         {
            if (fs::is_regular_file(entry) &&
               filter(entry))
            {
               result.push_back(entry);
            }
         }
      }

      return result;
   }

   void execute()
   {
      // find files containing prefix 'file_'
      {
         auto results = find_files(
            fs::current_path() / "test",
            [](fs::path const & p) { 
               auto filename = p.wstring();
               return filename.find(L"file_") != std::wstring::npos;
            });

         for (auto const & path : results)
         {
            std::cout << path << '\n';
         }
      }

      // find files with extension '.cpp'
      {
         auto results = find_files(
            fs::current_path() / "test",
            [](fs::path const & p) {
               return p.extension() == L".dat";
            });

         for (auto const & path : results)
         {
            std::cout << path << '\n';
         }
      }
   }
}