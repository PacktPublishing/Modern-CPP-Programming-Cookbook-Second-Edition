#pragma once

#include <fstream>
#include <iostream>
#include <filesystem>
#include <cassert>
#include <iomanip>
#include <chrono>

namespace fs = std::filesystem;

namespace recipe_7_10
{
   template <typename TP>
   std::time_t to_time_t(TP tp)
   {
      using namespace std::chrono;
      auto sctp = time_point_cast<system_clock::duration>(tp - TP::clock::now()
         + system_clock::now());
      return system_clock::to_time_t(sctp);
   }

   void execute()
   {
      auto path = fs::current_path() / "main.cpp";
      auto err = std::error_code{};

      // file exists
      {
         auto exists = fs::exists(path, err);
         std::cout << "file exists: " << std::boolalpha
            << exists << '\n';
      }

      // paths equivalent
      {
         auto same = fs::equivalent(
            path, 
            fs::current_path() / "." / "main.cpp", err);

         std::cout << "equivalent: " << same << '\n';
      }

      // file size
      {
         auto size = fs::file_size(path, err);
         std::cout << "file size: " << size << '\n';
      }

      // number of hard links
      {
         auto links = fs::hard_link_count(path, err);
         if(links != static_cast<uintmax_t>(-1))
            std::cout << "hard links: " << links << '\n';
         else
            std::cout << "hard links: error" << '\n';
      }

      // last write time
      {
         auto lwt = fs::last_write_time(path, err);
         auto time = to_time_t(lwt);
         auto localtime = std::localtime(&time);

         std::cout << "last write time: " 
            << std::put_time(localtime, "%c") << '\n';

         // modify last write time
         {
            using namespace std::chrono_literals;

            fs::last_write_time(path, lwt - 30min);

            lwt = fs::last_write_time(path, err);
            time = to_time_t(lwt);
            localtime = std::localtime(&time);

            std::cout << "last write time: "
               << std::put_time(localtime, "%c") << '\n';
         }
      }

      // status
      {
         auto print_perm = [](fs::perms p)
         {
            std::cout << ((p & fs::perms::owner_read) != fs::perms::none ? "r" : "-")
               << ((p & fs::perms::owner_write) != fs::perms::none ? "w" : "-")
               << ((p & fs::perms::owner_exec) != fs::perms::none ? "x" : "-")
               << ((p & fs::perms::group_read) != fs::perms::none ? "r" : "-")
               << ((p & fs::perms::group_write) != fs::perms::none ? "w" : "-")
               << ((p & fs::perms::group_exec) != fs::perms::none ? "x" : "-")
               << ((p & fs::perms::others_read) != fs::perms::none ? "r" : "-")
               << ((p & fs::perms::others_write) != fs::perms::none ? "w" : "-")
               << ((p & fs::perms::others_exec) != fs::perms::none ? "x" : "-")
               << '\n';
         };

         auto status = fs::status(path, err);
         std::cout << "type: " << static_cast<int>(status.type()) << '\n';
         std::cout << "permissions: ";
         print_perm(status.permissions());
      }

      // file types
      {
         std::cout << "regular file? " <<
            fs::is_regular_file(path, err) << '\n';
         std::cout << "directory? " <<
            fs::is_directory(path, err) << '\n';
         std::cout << "char file? " <<
            fs::is_character_file(path, err) << '\n';
         std::cout << "symlink? " <<
            fs::is_symlink(path, err) << '\n';

      }
   }
}
