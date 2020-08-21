#pragma once

#include <iostream>

namespace recipe_4_01
{
#if !defined(UNIQUE_NAME)
#define UNIQUE_NAME

   class widget
   {
   };

#endif

   void show_compiler()
   {
#if defined _MSC_VER
      std::cout << "Visual C++" << '\n';
#elif defined __clang__
      std::cout << "Clang" << '\n';
#elif defined __GNUG__
      std::cout << "GCC" << '\n';
#else
      std::cout << "Unknown compiler" << '\n';
#endif
   }

   void show_compiler_version()
   {
#if defined _MSC_VER
      
#if (_MSC_VER >= 1900)
      std::cout << "Visual C++ 2019 or newer\n";
#else 
      std::cout << "Visual C++ " << _MSC_FULL_VER << '\n';
#endif

#elif defined __clang__

#if (__clang_major__ == 3) && (__clang_minor__ >= 9)
      std::cout << "Clang 3.9 or newer\n";
#else
      std::cout << "Clang " << __clang_version__ << '\n';
#endif

#elif defined __GNUG__

#if __GNUC__ >= 5 && __GNUC_MINOR__ > 0
      std::cout << "GCC 5.0 or newer\n";
#else
      std::cout << "GCC " << __VERSION__ << '\n';
#endif

#else
      std::cout << "Unknown compiler" << '\n';
#endif
   }

   void show_architecture()
   {
#if defined _MSC_VER
      
#if defined _M_X64
      std::cout << "AMD64\n";
#elif defined _M_IX86
      std::cout << "INTEL x86\n";
#elif defined _M_ARM
      std::cout << "ARM\n";
#else
      std::cout << "unknown\n";
#endif

#elif defined __clang__ || __GNUG__

#if defined __amd64__
      std::cout << "AMD64\n";
#elif defined __i386__
      std::cout << "INTEL x86\n";
#elif defined __arm__
      std::cout << "ARM\n";
#else
      std::cout << "unknown\n";
#endif

#else
#error Unknown compiler
#endif
   }

   void show_configuration()
   {      
#ifdef _DEBUG
      std::cout << "debug\n";
#else
      std::cout << "release\n";
#endif
   }

   void execute()
   {
      show_compiler();

      show_compiler_version();

      show_architecture();

      show_configuration();
   }
}