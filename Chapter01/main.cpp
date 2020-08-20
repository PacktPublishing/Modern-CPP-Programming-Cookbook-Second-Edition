#include "features.h"
#include "recipe_1_01.h"
#include "recipe_1_02.h"
#include "recipe_1_03.h"
#include "recipe_1_04.h"
#include "recipe_1_05.h"
#include "recipe_1_06.h"
#include "recipe_1_07.h"
#include "recipe_1_08.h"
#include "recipe_1_09.h"
#include "recipe_1_10.h"
#include "recipe_1_11_1.h"
#include "recipe_1_11_2.h"
#include "recipe_1_12.h"
#include "recipe_1_13.h"
#include "recipe_1_14.h"

int main()
{
   recipe_1_01::execute();
   recipe_1_02::execute();
   recipe_1_03::execute();
   recipe_1_04::execute();
   recipe_1_05::execute();
   recipe_1_06::execute();
   recipe_1_07::execute();
   recipe_1_08::execute();
   recipe_1_09::execute();
   recipe_1_10::execute();
   recipe_1_11::file1_run();
   recipe_1_11::file2_run();
   recipe_1_12::client::execute();
   recipe_1_13::execute();
   recipe_1_14::execute();

   return 0;
}