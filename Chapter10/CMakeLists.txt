file(GLOB headers *.h ${headers})
add_executable(chapter10 main.cpp control.cpp ${headers})
include_directories(${CMAKE_SOURCE_DIR}/include)