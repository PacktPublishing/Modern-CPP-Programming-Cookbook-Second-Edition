file(GLOB headers *.h ${headers})
add_executable(chapter12_08 main.cpp ${headers})
include_directories(${CMAKE_SOURCE_DIR}/include)

if(MSVC)
  message(status "Suporting coroutines")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /await")
endif()
