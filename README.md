# Modern C++ Programming Cookbook - 2nd Edition
This is the code repository for **Modern C++ Programming Cookbook - 2nd Edition**, published by [Packt](https://www.packtpub.com/?utm_source=github). It contains all the supporting project files necessary to work through the book from start to finish.
## About the Book
Beginning with the modern language features, each recipe addresses a specific problem, with a discussion that explains the solution and offers insight into how it works. You will learn major concepts about the core programming language as well as common tasks faced while building a wide variety of software from enterprise grade apps to low latency software. You will learn about concepts such as concurrency, performance, testing, and more in the form of recipes. These recipes will ensure you can make your applications secure and fast.
## Instructions and Navigation
All of the code is organized into folders, one for each chapter. Some chapters contain one header file for each recipe in that chapter. In this cases, the header files are called recipe_1_01.h, recipe_1_02.h, etc. Other chapters, contain multiple programs, one for each recipe. In this case, in recipe has its own folder with names such as chapter12_01_1, chapter12_01_2, etc.

The code will look like the following:
```
    #include <iostream>

    int main()
    {
      std::cout << "Hello World!\n";
    }
```

The code presented in the book is available for download from your account at https://www.packtpub.com/, although I encourage you to try writing all the samples by yourself. In order to compile them, you need VC++ 2019 16.5 on Windows and GCC 10.0 or Clang 11.0 on Linux and Mac. If you don't have the latest version of the compiler, or you want to try another compiler, you can use one that is available online. Although there are various online platforms that you could use, I recommend https://wandbox.org/ or https://godbolt.org/.

## 3rd party libraries
The following libraries are required/optional for building the code:
| Libary | Path | Purpose |
| ------ | ---- | ------- |
| Boost.Test | https://www.boost.org/ | Testing projects in chapter 11 |
| Google Test | https://github.com/google/googletest | Testing projects in chapter 11 |
| Catch2 | https://github.com/catchorg/Catch2 | Testing projects in chapter 11 |
| Range-v3 | https://github.com/ericniebler/range-v3 | Ranges examples in chapter 12 |
| cppcoro | https://github.com/lewissbaker/cppcoro | Coroutines examples in chapter 12 |

## Building the code
The code can be build using CMake. The CMake files provided with the source code require CMake 3.15.0 or newer. The following values can be set:
* `SKIP_TEST_PROJECTS` Flag to prevent the generation of unit test projects (from chapter 11)
* `BOOST_PATH` Path to the installation path of Boost (required unless `SKIP_TEST_PROJECTS` is `ON`)
* `GTEST_PATH` Path to the installation path of Google Test (required unless `SKIP_TEST_PROJECTS` is `ON`)
* `GTEST_PATH_LIB` Path to the Google Test libraries directory (required unless `SKIP_TEST_PROJECTS` is `ON`)
* `CATCH_PATH` Path to the installation path of Catch2 (required unless `SKIP_TEST_PROJECTS` is `ON`)
* `RANGES_PATH` Path to the installation path of Ranges-v3 (required if `USE_RANGES_V3` is `ON`)
* `CPPCORO_PATH` Path to the installation path of cppcoro (required for chapter 12)

The following example shows how to generate projects for Visual Studio 2019:

```
cmake -G "Visual Studio 16 2019" -DBOOST_PATH=c:/Work/Libraries/boost_1_73_0/ -DGTEST_PATH=c:/Work/Libraries/googletest_1_10/googletest/include/ -DGTEST_PATH_LIB=c:/Work/Libraries/googletest_1_10/lib/ -DCATCH_PATH=c:/Work/Libraries/Catch2/single_include/ -DUSE_RANGES_V3=ON -DRANGES_PATH=c:/Work/Libraries/range-v3-master/include/ -DCPPCORO_PATH=c:/Work/Libraries/cppcoro-master -S .\ -B .\build
```

### Suggestions and Feedback
[Click here](https://docs.google.com/forms/d/e/1FAIpQLSe5qwunkGf6PUvzPirPDtuy1Du5Rlzew23UBp2S-P3wB-GcwQ/viewform) if you have any feedback or suggestions.
