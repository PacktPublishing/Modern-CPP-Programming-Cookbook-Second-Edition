#include "features.h"
#include "recipe_1_11_1.h"
#include <string>
#include <iostream>

using namespace std::string_literals;

namespace
{
   void print(std::string message)
   {
      std::cout << "[file1] " << message << '\n';
   }
}

namespace recipe_1_11
{
   void file1_run()
   {
      print("run"s);
   }
}