file(GLOB headers *.h)
add_executable(chapter02 main.cpp ${headers})
include_directories(${CMAKE_SOURCE_DIR}/include)