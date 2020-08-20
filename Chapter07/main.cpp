#include "recipe_7_01.h"
#include "recipe_7_02.h"
#include "recipe_7_03.h"
#include "recipe_7_04.h"
#include "recipe_7_05.h"
#include "recipe_7_06.h"
#include "recipe_7_07.h"
#include "recipe_7_08.h"
#include "recipe_7_09.h"
#include "recipe_7_10.h"
#include "recipe_7_11.h"
#include "recipe_7_12.h"

int main()
{
   recipe_7_01::execute();
   recipe_7_02::execute();
   recipe_7_03::execute();
   recipe_7_04::execute();
   recipe_7_05::execute();
   recipe_7_06::execute();
   recipe_7_07::execute();
   recipe_7_08::execute();
   recipe_7_09::execute();
   recipe_7_10::execute();
   recipe_7_11::execute();
   recipe_7_12::execute();

   fs::remove("sample.bin");

   return 0;
}