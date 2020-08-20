file(GLOB headers *.h)
add_executable(chapter01 main.cpp recipe_1_11_1.cpp recipe_1_11_2.cpp recipe_1_11_3.cpp ${headers})
include_directories(${CMAKE_SOURCE_DIR}/include)